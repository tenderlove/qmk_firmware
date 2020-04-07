require 'myhidapi'
require 'optparse'

class TeeloKB
  class Error < StandardError; end
  class CouldNotReadError < Error; end
  class KeyboardNotFoundError < Error; end

  COMMAND_VERSIONS = { 1 => {} }

  %i{
    version
    rgblight_enable
    rgblight_disable
    rgblight_toggle
    rgblight_mode
    rgblight_sethsv
    rgblight_get_mode
    rgblight_get_hue
    rgblight_get_sat
    rgblight_get_val
  }.each_with_index do |command, index|
    COMMAND_VERSIONS[1][command] = index + 1
  end

  def self.find
    MyHIDAPI.enumerate(0x0, 0x0).find { |dev| dev.product_string == "ErgoDox EZ" }
  end

  def self.open
    dev = self.find

    retries = 0
    handle = dev.open
    while !handle
      retries += 1
      raise KeyboardNotFoundError, "Couldn't find keyboard" if retries > 10
      handle = dev.open
    end

    new handle
  end

  def initialize handle
    @handle = handle
    @version = protocol_version
  end

  def protocol_version
    write [0x0, 0x1]
    read(2).inject(:+)
  end

  def solid
    rgblight_mode 0x1
  end

  def enable
    write [0x0, _(:rgblight_enable)]
    read 10
  end

  def disable
    write [0x0, _(:rgblight_disable)]
    read 10
  end

  def toggle
    write [0x0, _(:rgblight_toggle)]
    read 10
  end

  def mode
    write [0x0, _(:rgblight_get_mode)]
    read(2).last
  end

  def rainbow style = 0x6
    rgblight_mode style
  end

  def rgblight_mode value
    write [0x0, _(:rgblight_mode), value & 0xFF]
    read 10
  end
  alias :mode= :rgblight_mode

  def rgblight_sethsv h, s, v
    write([0x0, _(:rgblight_sethsv)] + [(h >> 8) & 0xFF, h & 0xFF, s & 0xFF, v & 0xFF])
    read 10
  end
  alias :sethsv :rgblight_sethsv

  def setrgb r, g, b
    sethsv(*rgb2hsv(r, g, b))
  end

  def hue
    write [0x0, _(:rgblight_get_hue)]
    _, upper, lower = read 3
    (upper << 8) | lower
  end

  def saturation
    write [0x0, _(:rgblight_get_sat)]
    read(2)[1]
  end

  def value
    write [0x0, _(:rgblight_get_val)]
    read(2)[1]
  end

  def hsv
    [hue, saturation, value]
  end

  private

  def rgb2hsv r, g, b
    v     = [r, g, b].max
    delta = v - [r, g, b].min

    s = v == 0 ? 0 : (delta / v.to_f)
    h = delta == 0 ? 0 : (case v
    when r then ((g - b) / delta) % 6
    when g then ((b - r) / delta) + 2
    when b then ((r - g) / delta) + 4
    end) * 60

    [h.round, (s * 255).round, v]
  end

  def write buf
    loop do
      break if @handle.write buf.pack('C*')
    end
  end

  def read size
    buf = @handle.read_timeout size, 300 # 300 ms timeout
    if buf
      buf.unpack('C*')
    else
      # Unfortunately, this seems to happen frequently.
      raise CouldNotReadError, "could not read from device"
    end
  end

  def _ command
    COMMAND_VERSIONS.fetch(@version).fetch(command)
  end
end

options   = { retry: true, attempt: 15 }
commands  = []
responses = []
args      = ARGV.dup

OptionParser.new do |opts|
  opts.banner = "Usage: #{__FILE__} [options]"

  opts.on("--hsv=[HSV]", "Set or get HSV (comma separated)") do |v|
    if v
      commands << lambda { |kb| kb.sethsv(*v.split(",").map(&:to_i)) }
    else
      commands << lambda { |kb| responses << { hsv: kb.hsv } }
    end
  end

  opts.on("--rgb=[RGB]", "Set or get RGB (comma separated)") do |v|
    if v
      commands << lambda { |kb| kb.setrgb(*v.split(",").map(&:to_i)) }
    else
      puts opts
      exit(1)
    end
  end

  opts.on("--mode=[MODE]", "Set or get mode (1 through 36)") do |v|
    if v
      commands << lambda { |kb| kb.mode = v.to_i }
    else
      commands << lambda { |kb| responses << { mode: kb.mode } }
    end
  end

  opts.on("--enable", "Enable")   { commands << lambda { |kb| kb.enable } }
  opts.on("--disable", "Disable") { commands << lambda { |kb| kb.disable } }
  opts.on("--fork", "Fork: not working") { options[:fork] = true }

  opts.on("--json", "Output as JSON") { options[:json] = true }
  opts.on("--no-retry", "Do not automatically retry command in case of failure") {
    options[:retry] = false
  }

  opts.on("--attempt=[NUM]", "Attempts left (used for automatic retry, do not set)") do |v|
    options[:attempt] = v.to_i
  end

  opts.on("-h", "--help", "Prints this help") do
    puts opts
    exit
  end
end.parse!

def main args, options, commands, responses
  begin
    kb = TeeloKB.open
    commands.each { |cmd| cmd.call kb }

    if options[:json] && responses.length > 0
      require 'json'
      puts JSON.dump responses
    else
      responses.each do |res|
        p res
      end
    end
  rescue TeeloKB::Error => e
    # This thing is really unreliable, so it retries by execing
    if options[:retry] && options[:attempt] > 0
      exec "ruby", __FILE__, "--attempt=#{options[:attempt] - 1}", *args
    else
      raise e
    end
  end
end

main args, options, commands, responses

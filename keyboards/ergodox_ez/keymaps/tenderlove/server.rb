require "webrick"

class HSVServlet < WEBrick::HTTPServlet::AbstractServlet
  LEDCTL = File.join File.expand_path(File.dirname(__FILE__)), 'ledctl.rb'

  def do_GET request, response
    hsv_info = `ruby #{LEDCTL} --hsv --json`

    response.status = 200
    response.content_type = "application/json"
    response.body = hsv_info
  end

  def do_POST request, response
    hsv = %w{ h s v }.map { |k| request.query[k] }.join(',')
    hsv_info = `ruby #{LEDCTL} --hsv=#{hsv} --json`

    response.status = 200
    response.content_type = "application/json"
    response.body = ''
  end
end

class ModeServlet < WEBrick::HTTPServlet::AbstractServlet
  LEDCTL = File.join File.expand_path(File.dirname(__FILE__)), 'ledctl.rb'

  def do_GET request, response
    response.status = 200
    response.content_type = "application/json"
    response.body = `ruby #{LEDCTL} --mode --json`

  end

  def do_POST request, response
    hsv_info = `ruby #{LEDCTL} --mode=#{request.query["mode"]} --json`

    response.status = 200
    response.content_type = "application/json"
    response.body = ''
  end
end

server = WEBrick::HTTPServer.new(:Port => 1234)
server.mount "/hsv", HSVServlet
server.mount "/mode", ModeServlet
server.mount "/", WEBrick::HTTPServlet::FileHandler, File.join(File.dirname(__FILE__), "public")

trap("INT") { server.shutdown }

Thread.new {
  sleep 0.5
  system "open http://localhost:1234"
}

server.start

require 'sinatra'

set :bind, '0.0.0.0'

counter = 0

get '/' do
	'Nothing'
end 

get '/esp' do 
	counter += 1 
	puts "#{counter} requests received"
end

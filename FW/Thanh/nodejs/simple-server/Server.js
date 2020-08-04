var http = require('http');
var fs = require('fs');
var server = http.createServer(function(request, response){
    if (request.url == '/server.html')
    {
        response.writeHead(200, {
            "Context-type" : "text/html"
        });
        fs.createReadStream('./server.html').pipe(response);
    }
    else 
    {
        response.writeHead(404, {
            "Context-type" : "text/plain"
        });
        response.write('404 Not Found ' + request.url);
         
        response.end();
    }
});
server.listen(3000, function(){
    console.log('Connected Successfull!');
});
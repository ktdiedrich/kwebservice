# kwebservice
Fast CGI Nginx web page service

## Resources 
http://chriswu.me/blog/writing-hello-world-in-fcgi-with-c-plus-plus/


## Configure Nginx
`/etc/nginx/sites-available/default`

```
...
location / {
		# First attempt to serve request as file, then
		# as directory, then fall back to displaying a 404.
		try_files $uri $uri/ =404;
		expires -1;
		fastcgi_pass   127.0.0.1:8000;

		fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
      		fastcgi_param  SERVER_SOFTWARE    nginx;
      		fastcgi_param  QUERY_STRING       $query_string;
      		fastcgi_param  REQUEST_METHOD     $request_method;
      		fastcgi_param  CONTENT_TYPE       $content_type;
      		fastcgi_param  CONTENT_LENGTH     $content_length;
      		fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
      		fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
      		fastcgi_param  REQUEST_URI        $request_uri;
      		fastcgi_param  DOCUMENT_URI       $document_uri;
      		fastcgi_param  DOCUMENT_ROOT      $document_root;
      		fastcgi_param  SERVER_PROTOCOL    $server_protocol;
      		fastcgi_param  REMOTE_ADDR        $remote_addr;
      		fastcgi_param  REMOTE_PORT        $remote_port;
      		fastcgi_param  SERVER_ADDR        $server_addr;
      		fastcgi_param  SERVER_PORT        $server_port;
      		fastcgi_param  SERVER_NAME        $server_name;
	}
	location ~ ^/~(.+?)(/.*)?$ {
        	 alias /home/$1/public_html$2;
         	 index index.html index.htm;
         	 autoindex on;
		 expires -1;
        }

```

## Compile 
`g++ project_pages.cgi.cpp -lfcgi++ -lfcgi -o project_pages.cgi`

## Spawn 
`spawn-fcgi -p 8000 -n project_pages.cgi`

## Web browser 
`http://localhost/`

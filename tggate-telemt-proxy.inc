proxy_http_version 1.1;
proxy_set_header Host $host;
proxy_set_header X-Forwarded-For $http_x_forwarded_for;
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection $tggate_connection_upgrade;

proxy_connect_timeout 5s;
proxy_send_timeout 65s;
proxy_read_timeout 65s;
proxy_request_buffering off;
proxy_buffering off;
proxy_next_upstream off;

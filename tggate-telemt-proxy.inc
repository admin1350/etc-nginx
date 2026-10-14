# /etc/nginx/tggate-telemt-proxy.inc

proxy_http_version 1.1;

# 1. Передача реального IP (самое важное для web_client_ip_source = "x_forwarded_for")
proxy_set_header Host $host;
proxy_set_header X-Real-IP $remote_addr;
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header X-Forwarded-Proto https; # Так как TLS терминируется на Caddy

# 2. Поддержка WebSocket (критично для современных web-транспортов mtg)
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection $connection_upgrade; # См. Шаг 2 про эту переменную

# 3. Отключение буферизации для потоковой передачи и long-polling
proxy_buffering off;
proxy_request_buffering off;
proxy_socket_keepalive on;

# 4. Таймауты (должны быть больше, чем long-polling в mtg, обычно 25-30с)
proxy_read_timeout 65s;
proxy_send_timeout 65s;

# ВАЖНО: Здесь НЕТ никаких add_header X-Frame-Options или CSP, 
# чтобы не сломать скрипт моста в WebView Telegram Desktop.

#proxy_http_version 1.1;
#proxy_set_header Host $host;
#proxy_set_header X-Forwarded-For $http_x_forwarded_for;
#proxy_set_header Upgrade $http_upgrade;
#proxy_set_header Connection $tggate_connection_upgrade;

#proxy_connect_timeout 5s;
#proxy_send_timeout 65s;
#proxy_read_timeout 65s;
#proxy_request_buffering off;
#proxy_buffering off;
#proxy_next_upstream off;

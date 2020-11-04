# base Ubuntu (Image)
FROM ubuntu:latest

# Install Nginx 
RUN apt-get update && apt-get install -y -q nginx

# File copy
COPY google_search.html ./

# RUN Nginx
CMD ["nginx", "-g", "daemon off;"]

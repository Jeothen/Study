# 1 layer  : base
FROM node:latest

# 2 layer : add app source 
RUN mkdir -p /app/src
# woriking directory가 없는 경우 생성
# -p : create app and source

WORKDIR /app/src
# woring directory를 지정

COPY package.json .
# . -> 현재 디렉토리 표시 == package.json /app/src  - package.json파일 복사

RUN npm install

COPY . .
# app of the app file copy to container :: source destination . - 현재 dir(상대경로) . - /app/src  == COPY . /app/src

EXPOSE 3000
# port number

CMD ["npm", "start"]



### command line
# docker images - all of the images

# docker ps  - container running or process running

# docker build . -t youtubereactapp   // -t tag지정

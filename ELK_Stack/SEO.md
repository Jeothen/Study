### Sitemap

* Site에 있는 페이지, 동영상 및 파일과 관계에 관한 정보를 제공하는 파일
* crawling을 통해 검색할 때 Site가 제대로 링크 되어야 함 
  * 동영상 항목의 경우 영상 길이, 카테고리, 연령 등의 정보를 포함
  * 이미지 항목은 주제, 유형 등을 포함
* Sitemap이 필요한 경우
  * 내부에 참조하는 페이지가 매우 많은 사이트인 경우 크롤러가 Skip 할 수 있음
  * 연결되는 외부 링크에 맞지 않는 사이트인 경우 링크를 타고 크롤링하는 크롤러가 제대로 찾을 수 없음
  * 인덱싱을 표시해야되는 영상이나 이미지 파일, 뉴스 페이지가 많은 경우 검색 결과에 표시하고자 할 때 Sitemap을 이용해 제공
* robots.txt : HTML 마크업 코드가 없고, 웹 서버에서 호스팅 됨
  * 사이트와 연결되어 있지 않아, crawling 하기 전, robots.txt 파일을 찾아 확인
  * 구성 
    * User-Agent : 어떤 종류의 로봇이 크롤링 할 수 있는지 확인
    * Disallow : 어떤 웹 페이지 url을 크롤링하면 안 되는지 명시
    * Allow : 특정 웹 페이지나 디렉터리에 접근하라는 명령
    * Crawl Delay : 서버를 과도하게 접근 못하게 delay를 부여

---





```h
<title> 태그의 내용이 검색 엔진에 노출
<meta>태그 각 페이지의 내용 설명 / 검색에서도 중요한 역할
url : 검색엔진이 문서를 크롤링하는데 중요
2개의 url에서 동일 내용의 내용이 있는 경우 <head>에 
	<link rel="canonical" href=""> 로 설정하거나, redirection 으로 설정

```



https://developers.google.com/search/docs/beginner/seo-starter-guide?hl=ko&visit_id=637409808201254627-1312250100&rd=2
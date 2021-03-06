# Search Engine

* 정보 수집 -> 인덱싱 -> 검색
* lucene 기반 엔진이 형태소 분석기, 색인 기능, 검색 기능 3가지를 모두 가지고 있음
  * 단순히 loop를 돌려 형태소를 분석하기에는 너무 많은 양이라 형태소를 분석하는 기술이 중요
  * 형태소 분석기를 통해 얻은 결과를 바탕으로 데이터를 빠르게 찾기 위해서는 색인을 사용
    * indexing을 사용하지 않으면 모든 데이터를 일일히 찾게 되어 비효율
    * 일반적으로 색인은 단어와 레코드 주소를 Key, Value 형태로 저장 (Inverted Indexing)
      * 찾아야하는 레코드 주소를 value로 설정해 value 내에 해당하는 문서만 탐색하여 사용자에게 전달

* 크롤러가 주기적으로 웹에 접속된 사이트들을 방문하여 웹 사이트가 가지고 있는 정보에 대한 인덱스를 작성한 후 데이터베이스에 저장 
  
* 크롤러 : 웹 상의 정보를 검색하고 인덱싱 하는 과정에서 사용되는 정보 수집 프로그램
  
* 사용자는 검색을 하게 되면 형태소 분석기를 통해 keyword로 나누어지고 keyword에 해당하는 index value를 데이터베이스로부터 가져와 사용자에게 보여주는 구조

---

### 검색 엔진 종류

1. Directory 검색 엔진
   * 검색하고자 하는 정보를 통해 주제 분류과 명확하게 되면 상당히 빠른 시간에 관련 정보를 찾을 수 있음
   * 큰 주제부터 작은 주제까지 범위를 좁혀가며 검색의 정확성을 높이는 방식
   * 대분류 -> 중분류 -> 소분류 등으로 찾아가는 방식이며, 현재 쓰이지 않음

2. 로봇 검색 엔진
   * 크롤러를 통해 웹 상의 데이터를 수집하고, keyword index를 통해 사용자에게 제공하는 엔진
   * google, naver 등에서 사용

3. 메타 검색 엔진
   * 멀티스레드 방식으로 한번의 검색으로 여러 검색 엔진을 동시에 검색한 후 가공 편집하여 사용자에게 제공
   * 독자적 데이터베이스를 가지고 있지 않음
   * 사용자가 원하지 않는 웹 페이지의 검색 결과가 노출되는 검색 noise가 발생

---

### 형태소 분석

...

----

### SEO 

* 검색 인젠의 인덱싱 작업을 돕는 기술
*  keyword같은 요소를 각각의 검색 엔진이 크롤링 하는 과정에 맞춰 검색 결과가 상위에 노출될 수 있게 함
* 웹 페이지에 keyword를 많이 추가하여 다른 웹 페이지에서 link 될 수 있게 함
  * 구글의 콘텐츠 신뢰도 파악이 타 사이트에서 인용되는 횟수로 평가하기 때문
* 네이버와 같은 한글의 포털 사이트는 자사 블로그가 우선 순위라 웹 문서가 아닌 블로그나 포스트로 등록하여 최적화 구성



https://developers.google.com/search/docs/beginner/seo-starter-guide?hl=ko&visit_id=637407854709551418-101076488&rd=1#google%EC%9D%84-%EC%82%AC%EC%9A%A9%ED%95%98%EA%B3%A0-%EA%B3%84%EC%8B%A0%EA%B0%80%EC%9A%94



https://developers.google.com/search?hl=ko


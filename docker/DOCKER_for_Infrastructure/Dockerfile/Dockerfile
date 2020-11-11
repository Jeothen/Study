# Docker 이미지 취득
FROM ubuntu:16.04

HEALTHCHECK --interval=100s --timeout=3s CMD curl -f http://localhost/ || exit 1

# top 실행
ENTRYPOINT ["top"]
CMD ["-d", "10"]

docker run -d --name gcc_container -it gcc /bin/bash
docker cp test.cpp gcc_container:/test.cpp
docker exec -it gcc_container ls /
docker exec -it gcc_container apt-get update
docker exec -it gcc_container g++ test.cpp -o test
docker exec -it gcc_container ls /
docker exec -it gcc_container ./test
docker exec -it gcc_container cat /test.cpp
docker stop gcc_container
docker rm gcc_container
    FROM gcc:5.5
    COPY . /BGCPPChallenge
    WORKDIR /BGCPPChallenge
    RUN g++ -o BGCPPChallenge xml_test.cpp
    CMD ["./BGCPPChallenge"]
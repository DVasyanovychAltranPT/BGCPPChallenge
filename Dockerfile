    FROM gcc:5.5
    COPY . /BGCPPChallenge
    WORKDIR /BGCPPChallenge
    RUN g++ -o BGCPPChallenge bggppchallenge.cpp
    CMD ["./BGCPPChallenge"]
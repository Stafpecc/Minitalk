FROM debian:latest

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc \
    make \
    valgrind \
    bash \
    git \
    sudo \
    build-essential \
    ca-certificates && \
    update-ca-certificates && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN make && make clean

RUN git clone https://github.com/ThibaudM13/minitalk-Tester.git minitalkTester && \
    chmod +x minitalkTester/tester.sh && \
    sed -i 's|PATH_TO_CLIENT=.*|PATH_TO_CLIENT="/app/client"|' minitalkTester/tester.sh

EXPOSE 4242

CMD ["sh", "-c", "./server & sleep 1 && ./minitalkTester/tester.sh $(pidof server) -m -b"]

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN chmod +x run_headless.sh

ENTRYPOINT ["./run_headless.sh"]
CMD []

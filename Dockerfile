FROM python:3.9-slim

WORKDIR /app

COPY main.py /app
RUN mkdir -p /output

CMD ["python", "main.py"]

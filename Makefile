all:
	g++ query.cpp -o query -O2 -lcrypto
	./query

clean:
	rm query
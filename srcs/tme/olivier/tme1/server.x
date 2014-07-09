struct message {
  char* message;
  int code;
};

struct request {
  string first<255>;
  string second<255>;
};

program SERVER {
	version SERVER_V1 {
		int sum(int) = 1;
		int print_message(struct message) = 2;
		string concat(struct request) = 3;
		int increment(void) = 4;
		int get(void) = 5;
	} = 1;
} = 0x2fffffff;

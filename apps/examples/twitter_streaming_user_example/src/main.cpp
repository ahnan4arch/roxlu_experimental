#include <iostream>
#include <twitter/Twitter.h>
#include <formats/json.h>
#include <unistd.h> // getpwd on linux
#include <libgen.h>// dirname

// Our callbacks
void on_filter_update_callback(const char* data, size_t len, void* user);

int main() {
  // On linux + mac, get the filepath to the SSL client key (see twitter addon readme on how to create one)
  char dir[1024];
  if(getcwd(dir, sizeof(dir)) == NULL) {
    printf("ERROR: Cannot get current directory: %s.\n", dir);
    ::exit(0);
  }
  char key_file[1024];
  sprintf(key_file, "%s/%s", dir, "data/client-key.pem");

  // Get a request-token, then exchange this token for a aouth token (see callback);
  roxlu::twitter::Twitter tw;
  tw.setSSLPrivateKey(key_file);
  tw.setConsumer("q8mQUYq7AEjGX4qD8lxSKw"); // Get this from your apps settings
  tw.setConsumerSecret("Uy3toRg4OXZqwuNTk9HYTaQLX977DenO0FG8rT5v6A"); // Get this from your apps settings

    /*
This file contains my private tokens, something like:
tw.setToken("TOKEN");
tw.setTokenSecret("SOME_TOKEN_SECRET");
   */
#include "twitter_tokens.h" 

  roxlu::twitter::TwitterStatusesFilter tsf("","466622389");
  tw.apiStatusesFilter(tsf, on_filter_update_callback);

  while(true) {
    tw.update();
  }
  return 0;
};

void on_filter_update_callback(const char* data, size_t len, void* user) {
  printf("%s\n", data);
  return;
}
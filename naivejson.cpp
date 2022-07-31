#include <assert.h>
#include "tinyjson.h"

typedef struct {
    const char* json;
} json_context;

int jsonParse(json_value* jv, const char* json) {
    json_context c;
    assert(jv != nullptr);
    c.json = json;
    jv->type = JSON_NULL;
    
}
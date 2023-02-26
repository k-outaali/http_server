#ifndef EXTENSIONS_H
#define EXTENSIONS_H

typedef enum {
    HTML,
    CSS,
    JS,
    JSON,
    XML,
    PHP,
    XHTML,
    UNKNOWN
}extension_t;

extension_t get_extension(char * filename);

#endif
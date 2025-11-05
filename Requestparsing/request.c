#include "request.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void freerequest(request_record *req) {
    free(req->reqline);
    free(req->host);
    free(req->user);
    free(req->accept);
    free(req->acceptl);
    free(req->accepte);
    free(req->connection);
    free(req->contentlength);
    free(req->cookie);
    free(req);
}

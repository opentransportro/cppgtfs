# cppgtfs

Parses GTFS feeds into memory. Extensive validation is applied. Currently used by LOOM and some student projects. Not perfect, but does the job.

## Usage

```
#include "ad/cppgtfs/Reader.h"

[...]

ad::cppgtfs::Reader parser("path/to/gtfs/folder");
ad::cppgtfs::gtfs::Feed feed;

parser.parse(&feed);
```

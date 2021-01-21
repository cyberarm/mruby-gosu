# mruby-gosu
mruby wrapper around [Gosu](https://github.com/gosu/gosu)

**Status:**
* Compatible with Gosu 0.15.2
* An [updated version](https://github.com/cyberarm/jcaster) of Jahmaican's original [jCaster](https://github.com/Jahmaican/jcaster) fully works.

## Usage
Add this mruby gem to your build_config.rb
```ruby
conf.gem github: "cyberarm/mruby-gosu"
```

## Development
* Install [Gosu](https://github.com/gosu/gosu) as a system library, [see wiki](https://github.com/gosu/gosu/wiki/Getting-Started-on-Linux#compiling-gosu-for-c).
(Note: may need to edit `gosu/build/cmake_install.cmake` to change `set(CMAKE_INSTALL_PREFIX "/usr/local")` to `set(CMAKE_INSTALL_PREFIX "/usr")`)

Note: ensure that mruby is compiled with `conf.cc.defines << "MRB_INT64"` or Gosu colors will trigger an integer overflow when compiling.

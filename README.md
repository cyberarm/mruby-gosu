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
### Unix
* Install [Gosu](https://github.com/gosu/gosu) as a system library, [see wiki](https://github.com/gosu/gosu/wiki/Getting-Started-on-Linux#compiling-gosu-for-c).
(Note: may need to edit `gosu/build/cmake_install.cmake` to change `set(CMAKE_INSTALL_PREFIX "/usr/local")` to `set(CMAKE_INSTALL_PREFIX "/usr")` before running `sudo make install`)

Sample MRuby Build Configuration
```ruby
MRuby::Build.new do |conf|
  conf.toolchain

  # include the default GEMs
  conf.gembox "default"

  conf.gem github: "cyberarm/mruby-gosu"
  conf.gem github: "mattn/mruby-require"

  # C compiler settings
  conf.cc.defines = %w(MRB_USE_DEBUG_HOOK MRB_INT64)
  conf.enable_debug
  conf.enable_cxx_abi
  conf.enable_test
end
```

### Windows
No instructions available yet.

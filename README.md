# mruby-gosu
mruby wrapper around [Gosu](https://github.com/gosu/gosu)

**Status:**
* Compatible with Gosu 1.4.3
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
* Clone Gosu
* Build Gosu as a `Release` for `x86` or `x64` with Visual Studio 19 or 22
* Copy the built `gosu-ffi.lib` file into to the `/gosu/lib/` directory or `/gosu/lib64/` for `x64`
* Visual Studio should have placed `Gosu.lib` into the same directory
* Open a MSYS2 console or use `$env:Path += ";PATH_TO_UCRT_BIN"` in PowerShell
* Build MRuby e.g. `rake MRUBY_CONFIG=gosu --verbose`
* Copy `gosu-ffi.dll` and `SDL2.dll` into `/mruby/bin/`

#### MSYS2 UCRT
Sample MRuby Build configuration
```ruby
MRuby::Build.new do |conf|
  conf.toolchain :gcc

  # include the default GEMs
  conf.gembox "default"

  conf.gem github: "cyberarm/mruby-gosu"
  conf.gem github: "mattn/mruby-require"

  # C compiler settings
  conf.cc.defines << "MRB_INT64"
  conf.cc.flags << "-fpermissive" # Needed for mruby-require
  conf.enable_cxx_abi
  conf.enable_debug
end
```

#### Visual C++
No instructions available yet.

MSYS2 UCRT's instructions might work with MSVC 140 sans `:gcc` (I had 143 installed)

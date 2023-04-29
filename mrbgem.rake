MRuby::Gem::Specification.new("mruby-gosu") do |spec|
  spec.license = "MIT"
  spec.authors = "cyberarm"
  spec.summary = "mruby bindings for the Gosu game library"

  # TODO: Support building on Windows MSVC
  # TODO: Don't hardcode Gosu FFI include path

  puts File.expand_path("../gosu/ffi")
  cc.include_paths << File.expand_path("../gosu/ffi")
  cxx.include_paths << File.expand_path("../gosu/ffi")
  cc.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
  cxx.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
  cc.flags << "/std:c++11"
  # cxx.flags << "/std:c++11"

  linker.library_paths << File.expand_path("../gosu/lib64")
  linker.libraries.push("gosu-ffi", "Gosu")
end

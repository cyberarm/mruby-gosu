MRuby::Gem::Specification.new("mruby-gosu") do |spec|
  spec.license = "MIT"
  spec.authors = "cyberarm"
  spec.summary = "mruby bindings for the Gosu game library"

  # TODO: Support building on Windows MSVC
  # TODO: Don't hardcode Gosu FFI include path

  if spec.for_windows?
    cc.include_paths << File.expand_path("../gosu/ffi")
    cxx.include_paths << File.expand_path("../gosu/ffi")
    cc.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
    cxx.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
    cc.flags << "-std=c++17"
    cxx.flags << "-std=c++17"

    linker.library_paths << "../gosu/lib64"
    linker.libraries.push("gosu-ffi", "Gosu")
  else
    cc.include_paths << File.expand_path("../gosu/ffi")
    linker.libraries << "gosu-ffi"
  end
end

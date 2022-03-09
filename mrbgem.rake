MRuby::Gem::Specification.new("mruby-gosu") do |spec|
  spec.license = "MIT"
  spec.authors = "cyberarm"
  spec.summary = "mruby bindings for the Gosu game library"

  # TODO: Support building on Windows MSVC
  # TODO: Don't hardcode Gosu FFI include path

  if spec.for_windows?
    spec.compilers.each do |c|
      c.include_paths << File.expand_path("../gosu/ffi")
      c.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
      c.flags << "-std=c++17"
    end

    linker.library_paths << "../gosu/lib64"
    linker.libraries.push("gosu-ffi", "Gosu")
  else
    cc.include_paths << File.expand_path("../gosu/ffi")
    linker.libraries << "gosu-ffi"
  end
end

MRuby::Gem::Specification.new("mruby-gosu") do |spec|
  spec.license = "MIT"
  spec.authors = "cyberarm"
  spec.summary = "mruby bindings for the Gosu game library"

  # TODO: Support building on Windows
  # TODO: Don't hardcode Gosu FFI include path
  cc.include_paths << File.expand_path("../gosu/ffi")
  linker.libraries << "gosu-ffi"
end

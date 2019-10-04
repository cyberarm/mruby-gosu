MRuby::Gem::Specification.new("mruby-gosu") do |spec|
  spec.license = "MIT"
  spec.authors = "cyberarm"
  spec.summary = "mruby bindings for the Gosu game library"

  spec.linker.libraries << "gosu"
end
module Gosu
  class Image
    def inititalize(path, retro: false, tileable: false)
      puts path, retro, tileable
      super(path, tileable, retro)
    end
  end
end
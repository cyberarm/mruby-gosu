module Gosu
  class Song
    def self.current_song
      nil
    end

    def play(looping = false)
      _play(looping)
    end
  end
end
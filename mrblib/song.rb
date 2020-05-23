module Gosu
  class Song
    def self.current_song
      if _current_song
        @@current_song
      else
        @@current_song = nil
        nil
      end
    end

    def play(looping = false)
      @@current_song = self
      _play(looping)
    end
  end
end
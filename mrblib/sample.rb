module Gosu
  class Sample
    def play(volume = 1, speed = 1, looping = false)
      _play(volume, speed, looping)
    end

    def play_pan(pan = 0, volume = 1, speed = 1, looping = false)
      _play_pan(pan, volume, speed, looping)
    end
  end
end
module Gosu
  class Window
    def initialize(width, height, fullscreen: false, update_interval: 16.6667, resizable: false)
      _new(width, height, fullscreen, update_interval, resizable)
    end

    def draw
    end

    def update
    end

    def button_down(id)
    end

    def button_up(id)
    end

    def needs_redraw?
      true
    end

    def needs_cursor?
      false
    end

    def drop(filename)
    end

    def close
      close!
    end
  end
end
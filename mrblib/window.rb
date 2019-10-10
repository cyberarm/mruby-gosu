module Gosu
  class Window
    # def initialize(width, height, compat_fullscreen = nil, compat_update_interval = nil, compat_resizable = nil,
    #                fullscreen: false, update_interval: 16.6667, resizable: false)

    #   fullscreen      = compat_fullscreen if compat_fullscreen != nil
    #   update_interval = compat_update_interval if compat_update_interval != nil
    #   resizable       = compat_resizable if compat_resizable != nil

    #   p width, height, fullscreen, update_interval, resizable

    #   super(width, height, fullscreen, update_interval, resizable)
    # end

    def update
    end

    def close
      close!
    end
  end
end
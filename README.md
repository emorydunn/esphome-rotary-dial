# ESPHome Rotary Dial

A custom ESPHome component that sends the dialed number to Home Assistant.

![Entity in Home Assistant](https://raw.githubusercontent.com/emorydunn/esphome-rotary-dial/main/images/hass_sensor.png)

# Installation

1. Copy `rotary_phone_sensor.h` to your `custom_components` folder
2. Include the file in your config

See `rotary_dial.yaml` for an example config.

# The Sensor

The only value the sensor exposes is an integer representing the number dialed, 0-9. The sensor doesn't dial multiple numbers, although it would be possible with some additional wiring and logic.

# Automations

The recomended way to respond to dialing is the `choose` action.


```yaml
alias: Rotary Dial
description: ''
trigger:
  - entity_id: sensor.rotary_dial
    platform: state
condition: []
action:
  - choose:
      - conditions:
          - condition: state
            entity_id: sensor.rotary_dial
            state: '1'
        sequence:
          - entity_id: scene.living_room_on
            service: scene.turn_on
      - conditions:
          - condition: state
            entity_id: sensor.rotary_dial
            state: '2'
        sequence:
          - entity_id: scene.living_room_off
            service: scene.turn_on
      - conditions:
          - condition: state
            entity_id: sensor.rotary_dial
            state: '3'
        sequence:
          - entity_id: scene.living_room_on
            service: scene.turn_on
          - entity_id: light.kitchen_lamp
            service: light.turn_on
      - conditions:
          - condition: state
            entity_id: sensor.rotary_dial
            state: '4'
        sequence:
          - entity_id: scene.living_room_off
            service: scene.turn_on
          - entity_id: light.kitchen_lamp
            service: light.turn_off
      - conditions:
          - condition: state
            entity_id: sensor.rotary_dial
            state: '6'
        sequence:
          - entity_id: scene.movies
            service: scene.turn_on
mode: single
```
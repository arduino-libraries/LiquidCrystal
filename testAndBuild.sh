#! /bin/sh
bundle install --path vendor/bundle
bundle exec arduino_ci_remote.rb

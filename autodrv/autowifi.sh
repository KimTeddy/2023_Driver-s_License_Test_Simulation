#!/bin/bash

# Add a new network
sudo wpa_cli add_network
if [ $? -eq 0 ]; then
    echo "add network successful!"
else
    echo "add network failed. Please check your settings."
fi
sleep 1
# Set the network SSID
sudo wpa_cli set_network 1 ssid '"kms mini"'
if [ $? -eq 0 ]; then
    echo "set network SSID successful!"
else
    echo "set network SSID failed. Please check your settings."
fi
sleep 1
# Set the network passphrase (PSK)
sudo wpa_cli set_network 1 psk '"13278649"'
if [ $? -eq 0 ]; then
    echo "set network Password successful!"
else
    echo "set network Password failed. Please check your settings."
fi
sleep 1
# Select the network
sudo wpa_cli select_network 1
if [ $? -eq 0 ]; then
    echo "select network successful!"
else
    echo "select network failed. Please check your settings."
fi
sleep 1
# Obtain IP address from DHCP
sudo dhclient wlan0
if [ $? -eq 0 ]; then
    echo "Successfully obtained the IP address!"
else
    echo "Failed to obtain IP address. Please check your settings."
fi

# Display network configuration
sudo ifconfig wlan0
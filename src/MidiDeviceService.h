#pragma once

#include <string>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Devices.Midi.h>
#include <winrt/Windows.Foundation.h>
#include "BLEAPER.h"

class MidiDeviceService
{
public:
	MidiDeviceService(winrt::hstring selector);
	~MidiDeviceService();
	void startWatching();
	void stopWatching();
	winrt::Windows::Devices::Enumeration::DeviceInformationCollection getDeviceInformationCollection() { return deviceInformationCollection; }
	void connectDevice(winrt::Windows::Devices::Enumeration::DeviceInformation const &deviceInfo);

private:
	void deviceWatcher_added(winrt::Windows::Devices::Enumeration::DeviceWatcher const &sender, winrt::Windows::Devices::Enumeration::DeviceInformation const &args);
	void deviceWatcher_removed(winrt::Windows::Devices::Enumeration::DeviceWatcher const &sender, winrt::Windows::Devices::Enumeration::DeviceInformationUpdate const &args);
	void deviceWatcher_updated(winrt::Windows::Devices::Enumeration::DeviceWatcher const &sender, winrt::Windows::Devices::Enumeration::DeviceInformationUpdate const &args);
	void deviceWatcher_enumerationCompleted(winrt::Windows::Devices::Enumeration::DeviceWatcher const &sender, winrt::Windows::Foundation::IInspectable args);
	void midiInPort_messageReceived(winrt::Windows::Devices::Midi::MidiInPort const &source, winrt::Windows::Devices::Midi::MidiMessageReceivedEventArgs const &args);
	void updateDevices();

private:
	bool enumerationCompleted = false;
	winrt::Windows::Devices::Enumeration::DeviceWatcher deviceWatcher{nullptr};
	winrt::hstring deviceSelector;
	winrt::event_token addedEventToken;
	winrt::event_token removedEventToken;
	winrt::event_token updatedEventToken;
	winrt::event_token enumerationCompletedEventToken;
	winrt::event_token messageReceivedEventToken;
	winrt::Windows::Devices::Enumeration::DeviceInformationCollection deviceInformationCollection{nullptr};
	winrt::Windows::Devices::Midi::MidiInPort currentDevice{nullptr};
};
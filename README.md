# Build 

[![Build Status](https://travis-ci.org/rumbler/QGoogleAnalytics.svg?branch=master)](https://travis-ci.org/rumbler/QGoogleAnalytics)

# QGoogleAnalytics
Qt Quick Plugin for Google Analytics

Integrate with Google Analytics to measure user interactions for your mobile and desktop apps.

It allows to track screen views and custom events to gain insights into your app's usage.
The three main methods for using the Google Analytics plugin and reports are
QGoogleAnalytics::logScreen, QGoogleAnalytics::logEvent and QGoogleAnalytics::logExcept

To use the plug-in requires two steps after
the installation:

    import the plugin
    Add a single instance of the item to the root item of your main.qml
    to call it from anywhere in your app.

## Example Usage

    main.qml

```
import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.3
import Indev.net.br.qgoogleanalytics 1.0 // import plugin

Window {
    id: main
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    // instance plugin
    QGoogleAnalytics {
        id: qa
        // enable sending data, Default false
        enabled: true
        // Property tracking ID from Google Analytics Dashboard
        tid: "UA-128496862-1"
        Component.onCompleted: qa.logScreen("Home")
    }

    Button {
        id: button
        text: qsTr("Buton")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: qa.logEvent("User Action", "Clik Button")
    }

    Component.onCompleted: qa.logScreen("Home")
}
```

#### The QGoogleAnalytics :: logScreen Method has an argument
    which defines the name of the screen.
    QGoogleAnalytics :: logException ("screen name")

#### The QGoogleAnalytics :: logEvent Method loads two arguments
    To define an event category and another to define the name
    of the event.
    QGoogleAnalytics :: logEvent ("User Action," "Clicked Button")

#### The QGoogleAnalytics :: logException Method loads two arguments
    being one of them obligatory and another not, having its fixed value by default.
    The first argument defines the description of the exception, and another defines
    whether the hit was fatal or not, taking as false by default.
    QGoogleAnalytics :: logException ("Not found database", true)

Example of use two cases:

###### In case of non-fatal error:
    QGoogleAnalytics :: logException ("Database not found")

###### In case of fatal error:
    QGoogleAnalytics :: logException ("Division by 0", true)

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    visible: true
    width: 400
    height: 500
    title: qsTr("Qt Client UI")

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        RowLayout
        {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.5
            spacing: 10

            Rectangle
            {
                radius: 10
                color: "lightgray"
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height * 0.5

                TextField
                {
                    id: ipField
                    anchors.fill: parent
                    placeholderText: "IP Address"
                    font.pixelSize: parent.height
                }
            }

            Rectangle
            {
                radius: 10
                color: "lightgray"
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height * 0.5

                TextField
                {
                    id: portField
                    anchors.fill: parent
                    placeholderText: "Port"
                    font.pixelSize: parent.height
                }
            }
        }

        Button
        {
            text: "Connect"
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.5
            onClicked: {
                client.connectToHost(ipField.text, parseInt(portField.text))
            }
        }
    }

    Connections
    {
        target: client

        function onReceived(data)
        {
            logArea.append("Received: " + data)
        }

        function onDisconnected()
        {
            logArea.append("Disconnected from server")
        }
    }
}

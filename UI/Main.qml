import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 6.0
import Aurora 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600
    title: "Console"

    ConsoleController
    {
        id: controller
    }

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: controller.model
            delegate: Text {
                text: model.text
                width: listView.width
                wrapMode: Text.Wrap
            }
            onCountChanged: listView.positionViewAtEnd()
        }

        TextField
        {
            id: inputField
            Layout.fillWidth: true
            placeholderText: "Enter command..."
            onAccepted: {
                controller.sendCommand(text)
                text = ""
            }
        }
    }

    Component.onCompleted: {
        controller.startProcess("C:/source/repos2/Aurora/Client/Dist/Aurora-Client.exe")
        inputField.forceActiveFocus()
    }
}

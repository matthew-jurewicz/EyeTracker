import QtQuick 2.0

Rectangle {
    id: messageDialog
    width: 252
    height: 127
    border.width: 1
    border.color: "#eeeeee"
    anchors.centerIn: parent

    signal okClicked()

    Rectangle {
        id: body
        width: 250
        height: 125
        anchors.centerIn: parent

        Rectangle {
            id: messageContainer
            width: parent.width
            height: 85

            Text {
                id: message
                text: qsTr("Connect to \"eyepiece_*\" WiFi, \nthen click OK.")
                font.pixelSize: 16
                anchors.centerIn: parent
            }
        }

        Rectangle {
            id: okButton
            width: parent.width
            height: 40
            anchors.top: messageContainer.bottom
            anchors.topMargin: 0
            color: "#eeeeee"

            Text {
                id: ok
                text: qsTr("OK")
                font.pixelSize: 17
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: messageDialog.okClicked()
            }
        }
    }
}

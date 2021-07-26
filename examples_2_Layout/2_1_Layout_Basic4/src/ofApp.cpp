#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);

	guiManager.setImGuiAutodraw(true); // -> required when only one single ImGui instance is instantiated on all the oF project.
	guiManager.setup();

	//-

	// ofParameters
	params1.setName("paramsGroup1");// main
	params1.add(bMode1.set("Mode1", false));
	params1.add(bMode2.set("Mode2", false));
	params1.add(bMode3.set("Mode3", false));
	params1.add(bMode4.set("Mode4", false));
	params1.add(bPrevious.set("<", false));
	params1.add(bNext.set(">", false));
	params1.add(bEnable.set("Enable", false));
	params1.add(lineWidth.set("lineWidth", 0.5, 0, 1));
	params1.add(separation.set("separation", 50, 1, 100));
	params1.add(speed.set("speed", 0.5, 0, 1));
	params1.add(shapeType.set("shapeType", 0, -50, 50));
	params1.add(size.set("size", 100, 0, 100));
	params1.add(amount.set("amount", 10, 0, 25));
}

static int _widgetId = 8953;

//--------------------------------------------------------------
void ofApp::draw()
{
	guiManager.begin();
	{
		if (!bInitiated) {
			bInitiated = true;

			//LoadConfigFile("config.xml");

			ImVec4 vViewport(10, 10, 1280, 720);
			LayoutManager::Instance()->InitAfterFirstDisplay(ImVec2((float)vViewport.z, (float)vViewport.w)); // will apply default layout if needed
		}

		if (LayoutManager::Instance()->BeginDockSpace(ImGuiDockNodeFlags_PassthruCentralNode))
		{
			//bool sCentralWindowHovered |= LayoutManager::Instance()->IsDockSpaceHoleHovered();
			LayoutManager::Instance()->EndDockSpace();
		}

		LayoutManager::Instance()->DisplayPanes(_widgetId);
		//_widgetId = LayoutManager::Instance()->DisplayPanes(_widgetId);
		ImVec2 vSize(400, 400);
		//LayoutManager::Instance()->InitAfterFirstDisplay(vSize);
		//LayoutManager::Instance()->DrawDialogsAndPopups();

		LayoutManager::Instance()->Init("Layouts", "Default Layout");
		//LayoutManager::Instance()->AddPane(SamplePane::Instance(), "Sample", (1 << 0), PaneDisposal::LEFT, true, true);

		drawMainWindow();

		//-

		//if (bOpen1)
		//{
		//	ImGuiWindowFlags window_flags;
		//	window_flags = ImGuiWindowFlags_None;
		//	if (bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		//	// window
		//	guiManager.beginWindow("Window 1", &bOpen1, window_flags);
		//	{
		//		drawWidgets();
		//	}
		//	guiManager.endWindow();
		//}
	}
	guiManager.end();
}


//--------------------------------------------------------------
void ofApp::drawWidgets()
{
	//guiManager.AddGroup(params1);

}

//--------------------------------------------------------------
void ofApp::drawMainWindow()
{
	ImGuiWindowFlags window_flags;
	window_flags = ImGuiWindowFlags_None;
	if (guiManager.bAutoResize) window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	{
		ImGui::Begin("Show Windows", &bOpen0, window_flags);
		{
			ofxImGuiSurfing::AddToggleRoundedButton(guiManager.bAutoResize);
			ofxImGuiSurfing::ToggleRoundedButton("Show Window 1", &bOpen1);
		}
		ImGui::End();
	}
}

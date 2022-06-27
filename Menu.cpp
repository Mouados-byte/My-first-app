#include "Menu.h"


void AlignForWidth(float width, float alignment = 0.5f)
{
    ImGuiStyle& style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
}

void AlignForHeight(float Height, float alignment = 0.2f)
{
    ImGuiStyle& style = ImGui::GetStyle();
    float avail = ImGui::GetContentRegionAvail().y;
    float off = (avail - Height) * alignment;
    if (off > 0.0f)
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + off);
}





void Menu::Render(ImGuiStyle* style, std::vector<LOGIN>& resources, std::vector<LOGIN>& new_content) {

    LOGIN container;
    static char nameL[128] = "";
    static char nameR[128] = "";
    static char passwdL[128] = "";
    static char passwdR[128] = "";
    if (settings::reg == 1) {
        
        
        auto text = "Login";
        float width = 0.0f, height = 0.0f;
        width += ImGui::CalcTextSize(text).x;
        height += ImGui::CalcTextSize(text).y;

        auto windowWidth = ImGui::GetWindowSize().x;
        auto windowHeight = ImGui::GetWindowSize().y;

        AlignForWidth(width);
        AlignForHeight(ImGui::CalcTextSize(text).y);
        ImGui::Text(text);
        //ImGui::Spacing();
        ImGui::PushItemWidth(215);
        AlignForWidth(215);
        AlignForHeight(13);
        
        //ImGui::SetCursorPosY(height);
        ImGui::InputTextWithHint("##name", "Enter Name here", nameL, IM_ARRAYSIZE(nameL));
        //ImGui::Spacing();
        AlignForWidth(215);
        //AlignForHeight(13);
        ImGui::InputTextWithHint("##passwd", "Enter password here", passwdL, IM_ARRAYSIZE(passwdL) , ImGuiInputTextFlags_Password);
        ImGui::PopItemWidth();
        
        
        AlignForHeight(41);
        AlignForWidth(215);
        if (ImGui::Button("Submit", ImVec2(230 - 15, 41))) {
            if (ifname(nameL)) {
                settings::reg = 3;
            }
        }
        AlignForHeight(41);
        AlignForWidth(ImGui::CalcTextSize("if you dont have an account:").x);
        ImGui::Text("if you dont have an account:");
        ImGui::Spacing();
        AlignForHeight(41);
        AlignForWidth(215);
        if (ImGui::Button("Register", ImVec2(230 - 15, 41))) {
                settings::reg = 2;
        }

    }
    if (settings::reg == 2) {
        static char str1[128] = "";

        AlignForWidth(ImGui::CalcTextSize("Name:").x);
        ImGui::Text("Name:");
        //ImGui::SameLine();
        ImGui::PushItemWidth(215);
        AlignForWidth(215);
        ImGui::InputTextWithHint("##inpname", "Enter Name here", nameR, IM_ARRAYSIZE(nameR));
        ImGui::SameLine();

        if (ImGui::Button("X", ImVec2(45, 25))) {
            strcpy_s(nameR, "\0");
        }
        ImGui::Spacing();
        AlignForWidth(215);
        ImGui::InputTextWithHint("##inppass", "Enter Password here", passwdR, IM_ARRAYSIZE(passwdR), ImGuiInputTextFlags_Password); 
        ImGui::SameLine();
        if (ImGui::Button("X", ImVec2(45, 25))) {
            strcpy_s(passwdR, "\0");
        }
        ImGui::PopItemWidth();
        
        ImGui::Spacing();
        style->Colors[ImGuiCol_Button] = ImColor(231, 130, 131, 255);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(231, 130, 131, 255);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);
        AlignForWidth(215);
        if (ImGui::Button("Register##insert", ImVec2(215, 41))) {
            if (!ifname(nameR)) {
                container.name = nameR;
                container.passwd = passwdR;
                resources.push_back(container);
                new_content.push_back(container);
                ImGui::Text("Done pushing");
                settings::reg = 3;
            }
            else {
                AlignForWidth(ImGui::CalcTextSize("This Username already exist, try another one").x);
                ImGui::TextColored(ImColor(255, 15, 15), "This Username already exist, try another one");
            }
        }

    }
    if (settings::reg == 3) {
        ImGui::Columns(2);
        ImGui::SetColumnOffset(1, 230);

        {
            ImGui::Spacing();
            if (ImGui::Button("See Login accounts##2", ImVec2(230 - 15, 41))) {
                settings::Tab = 1;
            }
            ImGui::Spacing();
            if (ImGui::Button("Show all data##3", ImVec2(230 - 15, 41))) {
                settings::Tab = 2;
            }
            ImGui::Spacing();
        }

        ImGui::NextColumn();


        {
            {
                
                //Dumper Tab
                if (settings::Tab == 1)
                {
                    static ImGuiTextFilter filter;


                    filter.Draw("Search", 240);
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
                    if (ImGui::ListBoxHeader("##ResourcesList"))
                    {
                        for (const auto& resource : resources)
                        {
                            if (filter.PassFilter(resource.name.c_str()))
                            {
                                //auto namer = resource.name.erase(0 , 1);
                                if (ImGui::TreeNode(resource.name.c_str()))
                                    ImGui::TreePop();
                                ImGui::SameLine();
                                if (ImGui::TreeNode(resource.passwd.c_str()))
                                    ImGui::TreePop();
                            }
                            
                        }
                        ImGui::ListBoxFooter();
                    }
                    ImGui::PopStyleColor();
                    if (ImGui::Button("Save to file##save", ImVec2(205, 34)))
                    {
                        writef(new_content);
                        ImGui::Text("Done pushing to the vec");
                        printf("Done writing");
                    }
                }
            }
        }

    }
}

void Menu::Theme(ImGuiStyle* style) {
    style->WindowBorderSize = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->WindowMinSize = ImVec2(900, 430);

    style->FramePadding = ImVec2(8, 6);

    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

    style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

    style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

    style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
}

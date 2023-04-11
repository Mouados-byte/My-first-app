#include "Menu.h"
#include "loader.h"
#include "sql.h"


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
    loader ld;
    LOGIN container;
    this_sql database;
    static char nameL[128] = "";
    static char nameR[128] = "";
    static char passwdL[128] = "";
    static char passwdR[128] = "";
    auto windowWidth = ImGui::GetWindowSize().x;
    auto windowHeight = ImGui::GetWindowSize().y;
    if (settings::reg == 1) {
        
        
        auto text = "Login";
        float width = 0.0f, height = 0.0f;
        width += ImGui::CalcTextSize(text).x;
        height += ImGui::CalcTextSize(text).y;

        

        AlignForWidth(width);
        AlignForHeight(ImGui::CalcTextSize(text).y);
        ImGui::Text(text);
        //ImGui::Spacing();
        ImGui::PushItemWidth(windowWidth/3);
        AlignForWidth(windowWidth/3);
        AlignForHeight(windowHeight/20);
        
        //ImGui::SetCursorPosY(height);
        ImGui::InputTextWithHint("##name", "Enter Name here", nameL, IM_ARRAYSIZE(nameL));
        //ImGui::Spacing();
        AlignForWidth(windowWidth/3);
        //AlignForHeight(13);
        ImGui::InputTextWithHint("##passwd", "Enter password here", passwdL, IM_ARRAYSIZE(passwdL) , ImGuiInputTextFlags_Password);
        ImGui::PopItemWidth();
        
        
        AlignForHeight(41);
        AlignForWidth(windowWidth/3);
        if (ImGui::Button("Submit", ImVec2(windowWidth/3, windowHeight/10))) {
            if (ifname(nameL)) {
                settings::reg = 3;
            }
        }
        AlignForHeight(windowHeight/10);
        AlignForWidth(ImGui::CalcTextSize("if you dont have an account:").x);
        ImGui::Text("if you dont have an account:");
        ImGui::Spacing();
        AlignForHeight(windowHeight/10);
        AlignForWidth(windowWidth/3);
        if (ImGui::Button("Register", ImVec2(windowWidth/3, 41))) {
                settings::reg = 2;
        }

    }
    if (settings::reg == 2) {
        static char str1[128] = "";

        AlignForWidth(ImGui::CalcTextSize("Name:").x);
        ImGui::Text("Name:");
        //ImGui::SameLine();
        ImGui::PushItemWidth(windowWidth/3);
        AlignForWidth(215);
        ImGui::InputTextWithHint("##inpname", "Enter Name here", nameR, IM_ARRAYSIZE(nameR));
        ImGui::SameLine();

        if (ImGui::Button("X", ImVec2(windowWidth/30, windowHeight/20))) {
            strcpy_s(nameR, "\0");
        }
        ImGui::Spacing();
        AlignForWidth(215);
        ImGui::InputTextWithHint("##inppass", "Enter Password here", passwdR, IM_ARRAYSIZE(passwdR), ImGuiInputTextFlags_Password); 
        ImGui::SameLine();
        if (ImGui::Button("X", ImVec2(windowWidth/30, windowHeight/20))) {
            strcpy_s(passwdR, "\0");
        }
        ImGui::PopItemWidth();
        
        ImGui::Spacing();
        style->Colors[ImGuiCol_Button] = ImColor(231, 130, 131, 255);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(231, 130, 131, 255);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);
        AlignForWidth(215);
        if (ImGui::Button("Register##insert", ImVec2(windowWidth/3, windowHeight/10))) {
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
        ImGui::SetColumnOffset(1, windowWidth/3);

        {
            ImGui::Spacing();
            if (ImGui::Button("See Login accounts##2", ImVec2(windowWidth / 3, windowHeight/10))) {
                settings::Tab = 1;
            }
            ImGui::Spacing();
            if (ImGui::Button("Show all data##3", ImVec2(windowWidth / 3, windowHeight/10))) {
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
                    database.data_sql();
                    if (ImGui::ListBoxHeader("##ResourcesList"))
                    {
                        int i = 0;
                        while (database.res->next() && i<5) {
                            if (filter.PassFilter(database.res->getString("first_name").c_str()))
                            {
                                //auto namer = resource.name.erase(0 , 1);
                                if (ImGui::TreeNode(database.res->getString("first_name").c_str()))
                                    ImGui::TreePop();
                                ImGui::SameLine();
                                if (ImGui::TreeNode(database.res->getString("last_name").c_str()))
                                    ImGui::TreePop();
                            }
                            i++;
                        }
                        ImGui::ListBoxFooter();
                    }
                    ImGui::PopStyleColor();
                    if (ImGui::Button("Save to file##save", ImVec2(windowWidth/3, windowHeight/13)))
                    {
                        writef(new_content);
                        ImGui::Text("Done pushing to the vec");
                        printf("Done writing");

                    }
                }
                if (settings::Tab == 2) {
                    
                    /*ld.ret = ld.LoadTextureFromFile("Resources/pop_cat.png", &ld.my_image_texture, &ld.my_image_width, &ld.my_image_height);
                    IM_ASSERT(ld.ret);
                    ImGui::Image((void*)(intptr_t)ld.my_image_texture, ImVec2(100,100));*/
                    ld.printtexture("Resources/pop_cat.png" , 200 , 150);
                    ImGui::SameLine();
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

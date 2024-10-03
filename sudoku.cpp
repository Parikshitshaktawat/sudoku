#include "include/sudoku.h"
#include "imgui/imgui.h"


int sudokuBoard[9][9] = {0}; // Initial empty board

void RenderSudokuBoard() {
    // Set background color to white
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White background

    // Set window size and center it
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 boardSize = ImVec2(450, 450);  // Fixed 450x450 size for 9x9 grid
    ImVec2 windowPos = ImVec2((io.DisplaySize.x - boardSize.x) * 0.5f, (io.DisplaySize.y - boardSize.y) * 0.5f);

    ImGui::SetNextWindowSize(boardSize);
    ImGui::SetNextWindowPos(windowPos);
    
    ImGui::Begin("Sudoku Board", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    const float cellSize = boardSize.x / 9.0f; // Equal cell size for each grid
    const float thickLineWidth = 4.0f;         // Thick black lines for 3x3 subgrid separators
    const float normalLineWidth = 1.0f;        // Normal line width for smaller cells
    const ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black color for lines

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0)); // Remove spacing between items

    // Drawing the board
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 p0 = ImGui::GetCursorScreenPos(); // Get the top-left corner of the window

    // Draw the cells (9x9 grid)
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            ImGui::PushID(row * 9 + col);
            
            // Set the input box size to be square and centered
            ImGui::SetNextItemWidth(cellSize * 0.8f); // Adjust width to fit within the cell

            // Initialize all cells with 0 if not already set
            if (sudokuBoard[row][col] == 0) {
                sudokuBoard[row][col] = 0; 
            }

            // Display input field for each cell with centered alignment
            ImGui::InputInt("##cell", &sudokuBoard[row][col], 0, 0, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_NoHorizontalScroll);
            // ImGui::SameLine(); // Keep the inputs on the same line

            // Calculate the position for each cell border
            ImVec2 cellPosMin = ImVec2(p0.x + col * cellSize, p0.y + row * cellSize);
            ImVec2 cellPosMax = ImVec2(cellPosMin.x + cellSize, cellPosMin.y + cellSize);

            // Add borders for each cell (normal line)
            drawList->AddRect(cellPosMin, cellPosMax, ImColor(blackColor), 0.0f, 0, normalLineWidth);

            ImGui::PopID();
            if (col < 8) ImGui::SameLine();
        }
    }

    // Draw the 3x3 thick lines
    for (int i = 0; i <= 9; i++) {
        float thickness = (i % 3 == 0) ? thickLineWidth : normalLineWidth;

        // Vertical lines for 3x3 subgrid separators
        ImVec2 verticalStart = ImVec2(p0.x + i * cellSize, p0.y);
        ImVec2 verticalEnd = ImVec2(p0.x + i * cellSize, p0.y + boardSize.y);
        drawList->AddLine(verticalStart, verticalEnd, ImColor(blackColor), thickness);

        // Horizontal lines for 3x3 subgrid separators
        ImVec2 horizontalStart = ImVec2(p0.x, p0.y + i * cellSize);
        ImVec2 horizontalEnd = ImVec2(p0.x + boardSize.x, p0.y + i * cellSize);
        drawList->AddLine(horizontalStart, horizontalEnd, ImColor(blackColor), thickness);
    }

    // Draw the outer border of the board
    drawList->AddRect(p0, ImVec2(p0.x + boardSize.x, p0.y + boardSize.y), ImColor(blackColor), 0.0f, 0, thickLineWidth);

    ImGui::PopStyleVar(); // Restore the style var

    ImGui::End();
}







// int sudokuBoard[9][9] = {0}; // Initial empty board, you can prefill it with numbers

// void RenderSudokuBoard() {
//     // Set background color to white
//     ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White background

//     // Set window size and center it
//     ImGuiIO& io = ImGui::GetIO();
//     ImVec2 boardSize = ImVec2(450, 450);  // Fixed 450x450 size for 9x9 grid
//     ImVec2 windowPos = ImVec2((io.DisplaySize.x - boardSize.x) * 0.5f, (io.DisplaySize.y - boardSize.y) * 0.5f);

//     ImGui::SetNextWindowSize(boardSize);
//     ImGui::SetNextWindowPos(windowPos);
    
//     ImGui::Begin("Sudoku Board", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

//     const float cellSize = boardSize.x / 9.0f; // Equal cell size for each grid
//     const float thickLineWidth = 4.0f;         // Thick black lines for 3x3 subgrid separators
//     const float normalLineWidth = 1.0f;        // Normal line width for smaller cells
//     const ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black color for lines

//     ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0)); // Remove spacing between items

//     // Drawing the board
//     ImDrawList* drawList = ImGui::GetWindowDrawList();
//     ImVec2 p0 = ImGui::GetCursorScreenPos(); // Get the top-left corner of the window

//     // Draw the cells (9x9 grid)
//     for (int row = 0; row < 9; row++) {
//         for (int col = 0; col < 9; col++) {
//             ImGui::PushID(row * 9 + col);

//             // Set the input box size to be square
//             ImGui::SetNextItemWidth(cellSize);

//             // Display input field for each cell with centered alignment
//             ImGui::InputInt("##cell", &sudokuBoard[row][col], 0, 0, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_NoHorizontalScroll);

//             // Calculate the position for each cell border
//             ImVec2 cellPosMin = ImVec2(p0.x + col * cellSize, p0.y + row * cellSize);
//             ImVec2 cellPosMax = ImVec2(cellPosMin.x + cellSize, cellPosMin.y + cellSize);

//             // Add borders for each cell (normal line)
//             drawList->AddRect(cellPosMin, cellPosMax, ImColor(blackColor), 0.0f, 0, normalLineWidth);

//             ImGui::PopID();
//             if (col < 8) ImGui::SameLine();
//         }
//     }

//     ImGui::PopStyleVar(); // Restore the style var

//     // Draw the 3x3 thick lines
//     for (int i = 0; i <= 9; i++) {
//         float thickness = (i % 3 == 0) ? thickLineWidth : normalLineWidth;

//         // Vertical lines for 3x3 subgrid separators
//         ImVec2 verticalStart = ImVec2(p0.x + i * cellSize, p0.y);
//         ImVec2 verticalEnd = ImVec2(p0.x + i * cellSize, p0.y + boardSize.y);
//         drawList->AddLine(verticalStart, verticalEnd, ImColor(blackColor), thickness);

//         // Horizontal lines for 3x3 subgrid separators
//         ImVec2 horizontalStart = ImVec2(p0.x, p0.y + i * cellSize);
//         ImVec2 horizontalEnd = ImVec2(p0.x + boardSize.x, p0.y + i * cellSize);
//         drawList->AddLine(horizontalStart, horizontalEnd, ImColor(blackColor), thickness);
//     }

//     ImGui::End();
// }

// int sudokuBoard[9][9] = {0}; // Initial empty board

// void RenderSudokuBoard() {
//     // Set background color to white
//     ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White background

//     // Set window size and center it
//     ImGuiIO& io = ImGui::GetIO();
//     ImVec2 boardSize = ImVec2(450, 450);  // Fixed 450x450 size for 9x9 grid
//     ImVec2 windowPos = ImVec2((io.DisplaySize.x - boardSize.x) * 0.5f, (io.DisplaySize.y - boardSize.y) * 0.5f);

//     ImGui::SetNextWindowSize(boardSize);
//     ImGui::SetNextWindowPos(windowPos);
    
//     ImGui::Begin("Sudoku Board", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

//     const float cellSize = boardSize.x / 9.0f; // Equal cell size for each grid
//     const float thickLineWidth = 4.0f;         // Thick black lines for 3x3 subgrid separators
//     const float normalLineWidth = 1.0f;        // Normal line width for smaller cells
//     const ImVec4 blackColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black color for lines

//     ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0)); // Remove spacing between items

//     // Drawing the board
//     ImDrawList* drawList = ImGui::GetWindowDrawList();
//     ImVec2 p0 = ImGui::GetCursorScreenPos(); // Get the top-left corner of the window

//     // Draw the cells (9x9 grid)
//     for (int row = 0; row < 9; row++) {
//         for (int col = 0; col < 9; col++) {
//             ImGui::PushID(row * 9 + col);

//             // Set the input box size to be square
//             ImGui::SetNextItemWidth(cellSize);

//             // Display input field for each cell with centered alignment
//             if (sudokuBoard[row][col] == 0) {
//                 sudokuBoard[row][col] = 0; // Initialize all cells with 0
//             }
//             ImGui::InputInt("##cell", &sudokuBoard[row][col], 0, 0, ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_NoHorizontalScroll);

//             // Calculate the position for each cell border
//             ImVec2 cellPosMin = ImVec2(p0.x + col * cellSize, p0.y + row * cellSize);
//             ImVec2 cellPosMax = ImVec2(cellPosMin.x + cellSize, cellPosMin.y + cellSize);

//             // Add borders for each cell (normal line)
//             drawList->AddRect(cellPosMin, cellPosMax, ImColor(blackColor), 0.0f, 0, normalLineWidth);

//             ImGui::PopID();
//             if (col < 8) ImGui::SameLine();
//         }
//     }

//     // Draw the 3x3 thick lines
//     for (int i = 0; i <= 9; i++) {
//         float thickness = (i % 3 == 0) ? thickLineWidth : normalLineWidth;

//         // Vertical lines for 3x3 subgrid separators
//         ImVec2 verticalStart = ImVec2(p0.x + i * cellSize, p0.y);
//         ImVec2 verticalEnd = ImVec2(p0.x + i * cellSize, p0.y + boardSize.y);
//         drawList->AddLine(verticalStart, verticalEnd, ImColor(blackColor), thickness);

//         // Horizontal lines for 3x3 subgrid separators
//         ImVec2 horizontalStart = ImVec2(p0.x, p0.y + i * cellSize);
//         ImVec2 horizontalEnd = ImVec2(p0.x + boardSize.x, p0.y + i * cellSize);
//         drawList->AddLine(horizontalStart, horizontalEnd, ImColor(blackColor), thickness);
//     }

//     // Draw the outer border of the board
//     drawList->AddRect(p0, ImVec2(p0.x + boardSize.x, p0.y + boardSize.y), ImColor(blackColor), 0.0f, 0, thickLineWidth);

//     ImGui::PopStyleVar(); // Restore the style var

//     ImGui::End();
// }

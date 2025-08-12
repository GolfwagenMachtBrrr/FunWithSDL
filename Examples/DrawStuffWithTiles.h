
/*
SDL_Window* window=nullptr;
SDL_Init(SDL_INIT_VIDEO);
int windowWidth = 1920, windowHeight = 1080;
window = SDL_CreateWindow("C++ SDL2 Window",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,SDL_WINDOW_SHOWN);

SDL_Renderer* renderer = nullptr;
renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

SDL_Surface* tile_map_surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/tiles.bmp");
SDL_Surface* empty_map_surface = SDL_LoadBMP("/home/judelhuu/CLionProjects/SDL_Tutorial/Images/Tiles/error.bmp");

SDL_Texture* tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
SDL_Texture* empty_texture = SDL_CreateTextureFromSurface(renderer, empty_map_surface);

SDL_FreeSurface(tile_map_surface);
SDL_FreeSurface(empty_map_surface);


// ImGui Init
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;
ImGui::StyleColorsDark();

ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
ImGui_ImplSDLRenderer2_Init(renderer);

// Center area
SDL_Rect center;
int centersizeX = 1024, centersizeY = 528;
int centerposX = (windowWidth - centersizeX) / 2,
    centerposY = (windowHeight - centersizeY) / 2;
center.x = centerposX;
center.y = centerposY;
center.w = centersizeX;
center.h = centersizeY;

// helper variables
constexpr int tilesize = 16;
constexpr int selectiontiles = 16;
const int chunksize = centersizeX/tilesize * centersizeY/tilesize;

const int tilesX = centersizeX/tilesize;
const int tilesY = centersizeY/tilesize;

// Selection area
SDL_Rect selection;
int selectionposX = 64, selectionposY = 1080/2 - 256;
int selectionsizeX = 256, selectionsizeY = 256;
selection.x = selectionposX;
selection.y = selectionposY;
selection.w = selectionsizeX;
selection.h = selectionsizeY;

// camera
SDL_Rect camera = {0,0 , centersizeX, centersizeY};

// map
std::map<std::pair<int, int>, Chunk> worldChunks;


// tiles (textured rectangles)
std::vector<std::vector<std::unique_ptr<Tile>>> center_tilemap;
std::vector<std::vector<std::unique_ptr<Tile>>> selection_tilemap;
// grid to render textured rects to
std::vector<std::vector<std::unique_ptr<SDL_Rect>>> center_grid;
std::vector<std::vector<std::unique_ptr<SDL_Rect>>> selection_grid;
// stores tile coords
std::vector<std::pair<int,int>> selection_tiles;


// tiles center
for (int x = 0; x < tilesX; x++ )
{
    std::vector<std::unique_ptr<Tile>> tilemap_row;
    for (int y = 0; y < tilesY; y++)
    {
        std::unique_ptr<Tile> tilemap_tile = std::make_unique<Tile>();

        tilemap_tile->tiletype = 5;
        tilemap_tile->rendertype = DEFAULT;

        tilemap_tile->visible = true;
        tilemap_tile->copyactive = true;

        tilemap_tile->rectangle.x = x*tilesize + centerposX;
        tilemap_tile->rectangle.y = y*tilesize + centerposY;
        tilemap_tile->rectangle.w = tilesize;
        tilemap_tile->rectangle.h = tilesize;

        tilemap_row.push_back(std::move(tilemap_tile));
    }
    center_tilemap.push_back(std::move(tilemap_row));
}
// grid center
for (int x = 0; x < tilesX; x++ )
{
    std::vector<std::unique_ptr<SDL_Rect>> grid_row;
    for (int y = 0; y < tilesY; y++)
    {
        auto grid_tile = std::make_unique<SDL_Rect>();

        grid_tile->x = x*tilesize;
        grid_tile->y = y*tilesize;
        grid_tile->w = tilesize;
        grid_tile->h = tilesize;

        grid_row.push_back(std::move(grid_tile));
    }
    center_grid.push_back(std::move(grid_row));
}
// tiles selection
for (int x = 0; x < selectiontiles; x++ )
{
    std::vector<std::unique_ptr<Tile>> selectionmap_row;
    for (int y = 0; y < selectiontiles; y++)
    {
        auto selectionmap_tile = std::make_unique<Tile>();

        selectionmap_tile->tiletype = y + x*selectiontiles;
        selectionmap_tile->rendertype = DEFAULT;

        selectionmap_tile->visible = true;
        selectionmap_tile->copyactive = false;

        selectionmap_tile->rectangle.x = x*tilesize;
        selectionmap_tile->rectangle.y = y*tilesize;
        selectionmap_tile->rectangle.w = tilesize;
        selectionmap_tile->rectangle.h = tilesize;

        // Get tile coords
        selection_tiles.push_back(std::make_pair(selectionmap_tile->rectangle.x/16, selectionmap_tile->rectangle.y/16));

        selectionmap_row.push_back(std::move(selectionmap_tile));
    }
    selection_tilemap.push_back(std::move(selectionmap_row));
}
//grid selection
for (int x = 0; x < selectiontiles; x++ )
{
    std::vector<std::unique_ptr<SDL_Rect>> selectiongrid_row;
    for (int y = 0; y < selectiontiles; y++)
    {
        auto selectiongrid_tile = std::make_unique<SDL_Rect>();

        selectiongrid_tile->x = x*tilesize + selectionposX;
        selectiongrid_tile->y = y*tilesize + selectionposY;

        selectiongrid_tile->w = tilesize;
        selectiongrid_tile->h = tilesize;

        selectiongrid_row.push_back(std::move(selectiongrid_tile));
    }
    selection_grid.push_back(std::move(selectiongrid_row));
}

// helper variables (gameloop)
bool isRunning = true;

int center_mouseX, center_mouseY;
int selection_mouseX, selection_mouseY;

int selection_mousetileX, selection_mousetileY;
int center_mousetileX, center_mousetileY;

int savedmousetileY = -1, savedmousetileX = -1; // (selection)

while (isRunning)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_MOUSEMOTION) {
            SDL_GetMouseState(&selection_mouseX, &selection_mouseY);

            // relative to camera coords
            center_mouseX = selection_mouseX + camera.x;
            center_mouseY = selection_mouseY + camera.y;

            // mouse is in selection area
            if (selection_mouseX > selectionposX && selection_mouseX < selectionposX+selectionsizeX &&
                selection_mouseY > selectionposY && selection_mouseY < selectionposY+selectionsizeY)
            {
                if (selection_mousetileX > 0 && selection_mousetileY > 0) {
                    // reset rendertype to DEFAULT if not SELECTED
                    if (selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype == IN_SELECTION) {
                        selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype = DEFAULT;
                    }
                }

                // storing indecies of the selected tiles (selection)
                selection_mousetileX = (selection_mouseX-selectionposX)/tilesize;
                selection_mousetileY = (selection_mouseY-selectionposY)/tilesize;


                // Tiles at the stored coords become IN_SELECTION  (SELECTED dont become IN_SELECTION)
                if (selection_mousetileX > 0 && selection_mousetileX < selectiontiles &&
                    selection_mousetileY > 0 && selection_mousetileY < selectiontiles)
                {
                    if (selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype != SELECTED &&
                        selection_tilemap[selection_mousetileX][selection_mousetileY]->visible)
                    {
                        selection_tilemap[selection_mousetileX][selection_mousetileY]->rendertype = IN_SELECTION;
                    }
                }
            }

            // mouse is in center area
            if (center_mouseX > centerposX && center_mouseX < centerposX+centersizeX &&
                center_mouseY > centerposY && center_mouseY < centerposY+centersizeY)
            {
                // if in range
                if (center_mousetileX >= 0 && center_mousetileX < tilesX &&
                    center_mousetileY >= 0 && center_mousetileY < tilesY)

                {
                    // reset rendertype to DEFAULT if IN_SELECTION
                    if (center_tilemap[center_mousetileX][center_mousetileY]->rendertype == IN_SELECTION) {
                        center_tilemap[center_mousetileX][center_mousetileY]->rendertype = DEFAULT;
                    }
                }

                // storing indecies of the selected tiles (center)
                center_mousetileX = (center_mouseX-centerposX)/tilesize;
                center_mousetileY = (center_mouseY-centerposY)/tilesize;

                // Tiles at the stored coords become IN_SELECTION  (SELECTED dont become IN_SELECTION)
                if (center_mousetileX >= 0 && center_mousetileX < tilesX &&
                    center_mousetileY >= 0 && center_mousetileY < tilesY)
                {
                    if (center_tilemap[center_mousetileX][center_mousetileY]->rendertype != SELECTED &&
                        center_tilemap[center_mousetileX][center_mousetileY]->visible)
                    {
                        center_tilemap[center_mousetileX][center_mousetileY]->rendertype = IN_SELECTION;
                    }
                }
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                std::cout << "CenterX: " << center_mousetileX << " CenterY: " << center_mousetileY <<std::endl;
                std::cout << "SelectionX: " << selection_mousetileX << " SelectionY: " << selection_mousetileY <<std::endl;


                // mouse is in SELECTION area
                if (selection_mouseX > selectionposX && selection_mouseX < selectionposX+selectionsizeX &&
                 selection_mouseY > selectionposY && selection_mouseY < selectionposY+selectionsizeY)
                {
                    // storing indecies of the selected tiles (selection)
                    savedmousetileX = selection_mousetileX, savedmousetileY = selection_mousetileY;

                    // activate copy mode (selection)
                    selection_tilemap[savedmousetileX][savedmousetileY]->copyactive = true;
                    selection_tilemap[savedmousetileX][savedmousetileY]->rendertype = SELECTED;
                }

                // mouse is in CENTER area
                if (center_mouseX > centerposX && center_mouseX < centerposX+centersizeX &&
                    center_mouseY > centerposY && center_mouseY < centerposY+centersizeY)
                {
                    // enable visibility
                    center_tilemap[center_mousetileX][center_mousetileY]->visible = true;
                    center_tilemap[center_mousetileX][center_mousetileY]->rendertype = DEFAULT;

                    // assign default tyletype
                    center_tilemap[center_mousetileX][center_mousetileY]->rectangle.x = selection_tiles[0].first;
                    center_tilemap[center_mousetileX][center_mousetileY]->rectangle.y = selection_tiles[0].second;


                    // savedmousetileX must contain a value
                    if (savedmousetileX != -1 && savedmousetileY != -1)
                    {
                        // check wheter copy is active (enabled)
                        if (selection_tilemap[savedmousetileX][savedmousetileY]->copyactive &&
                            center_tilemap[center_mousetileX][center_mousetileY]->copyactive)
                        {
                            // tiletype gets copied
                            center_tilemap[center_mousetileX][center_mousetileY]->tiletype =
                                selection_tilemap[savedmousetileX][savedmousetileY]->tiletype;

                            center_tilemap[center_mousetileX][center_mousetileY]->rectangle.x =
                                selection_tiles[center_tilemap[center_mousetileX][center_mousetileY]->tiletype].first;

                            center_tilemap[center_mousetileX][center_mousetileY]->rectangle.y =
                                selection_tiles[center_tilemap[center_mousetileX][center_mousetileY]->tiletype].second;
                        }
                    }

                }
            }
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                // deactivate copy mode
                if (selection_mousetileX > 0 && selection_mousetileX < tilesX &&
                    selection_mousetileY > 0 && selection_mousetileY < tilesY)
                {
                    selection_tilemap[savedmousetileX][savedmousetileY]->copyactive = false;
                    selection_tilemap[savedmousetileX][savedmousetileY]->rendertype = DEFAULT;
                }
            }
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_RIGHT:
                    camera.x += tilesize;
                    // Kamera nicht über Tilemap hinaus bewegen
                    if (camera.x > tilesX * tilesize - camera.w)
                        camera.x = tilesX * tilesize - camera.w;
                    break;
                case SDL_SCANCODE_LEFT:
                    camera.x -= tilesize;
                    if (camera.x < 0) camera.x = 0;
                    break;
                case SDL_SCANCODE_DOWN:
                    camera.y += tilesize;
                    if (camera.y > tilesY * tilesize - camera.h)
                        camera.y = tilesY * tilesize - camera.h;
                    break;
                case SDL_SCANCODE_UP:
                    camera.y -= tilesize;
                    if (camera.y < 0) camera.y = 0;
                    break;
                default:
                    break;
            }
            }
    }

    // Set Background color Black
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render ImGui
    static float somefloat = 0;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();

    ImGui::Begin("Hello ImGui");
    ImGui::Text("SDL2 Renderer backend");
    ImGui::SliderFloat("float", &somefloat, 0.0f, 1.0f);

    ImGui::Image((ImTextureID)(intptr_t)tile_texture, ImVec2(256,256));
    ImGui::End();
    ImGui::Render();

    // Render areas
    SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &center);
    SDL_RenderDrawRect(renderer, &selection);

    // render selectionmap
    for (int x = 0; x < selectiontiles; x++) {
        for (int y = 0; y < selectiontiles; y++) {
            const SDL_Rect* tilemap_tile = &selection_tilemap[x][y].get()->rectangle;
            const SDL_Rect* grid_tile = selection_grid[x][y].get();

            switch (selection_tilemap[x][y]->rendertype) // durch enums ersetzen
            {
                case DEFAULT:
                    SDL_RenderCopy(renderer, tile_texture, tilemap_tile, grid_tile);
                    break;
                case IN_SELECTION:
                    SDL_SetTextureColorMod(tile_texture, 255, 0, 0);
                    SDL_RenderCopy(renderer, tile_texture, tilemap_tile, grid_tile);
                    SDL_SetTextureColorMod(tile_texture, 255, 255, 255);
                    break;
                case SELECTED:
                    SDL_SetTextureColorMod(tile_texture, 0, 0, 255);
                    SDL_RenderCopy(renderer, tile_texture, tilemap_tile, grid_tile);
                    SDL_SetTextureColorMod(tile_texture, 255, 255, 255);
                    break;
                default:
                    break;
            }
        }
    }

    // render tilemap
    for (int x = 0; x < tilesX; ++x) {
        for (int y = 0; y < tilesY; ++y) {
            int tileScreenX = x * tilesize - camera.x + centerposX;
            int tileScreenY = y * tilesize - camera.y + centerposY;

            // Nur rendern, wenn Tile sichtbar im Zentrum (Clipping)
            if (tileScreenX + tilesize < centerposX || tileScreenX > centerposX + centersizeX ||
                tileScreenY + tilesize < centerposY || tileScreenY > centerposY + centersizeY)
                continue;

            SDL_Rect src_tile = {
                selection_tiles[center_tilemap[x][y]->tiletype].first * tilesize,
                selection_tiles[center_tilemap[x][y]->tiletype].second * tilesize,
                tilesize,
                tilesize
            };

            SDL_Rect dst_tile = {
                tileScreenX,
                tileScreenY,
                tilesize,
                tilesize
            };

            switch (center_tilemap[x][y]->rendertype)
            {
                case EMPTY:
                    SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawRect(renderer,&dst_tile);
                    break;
                case DEFAULT:
                    SDL_SetRenderDrawColor(renderer, 0,0,0,SDL_ALPHA_OPAQUE);
                    SDL_RenderCopy(renderer, tile_texture, &src_tile, &dst_tile);
                    break;
                case IN_SELECTION:
                    SDL_SetTextureColorMod(tile_texture, 255, 0, 0);
                    SDL_RenderCopy(renderer, tile_texture, &src_tile, &dst_tile);
                    SDL_SetTextureColorMod(tile_texture, 255, 255, 255);
                    break;
                default:
                    break;
            }
        }
    }
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),renderer);
    SDL_RenderPresent(renderer);
}
*/



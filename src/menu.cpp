#include "menu.hpp"

Menu::Menu(TTF_Font *font, TTF_Font *item_font, SDL_Renderer *renderer, SDL_Color title_color, SDL_Color item_color, SDL_Color active_item_color,
           int title_dst_w, int title_dst_h)
{
    this->title_font = font;
    this->item_font = item_font;
    this->renderer = renderer;
    this->title_color = title_color;
    this->item_color = item_color;
    this->active_item_color = active_item_color;
    this->title_dst_w = title_dst_w;
    this->title_dst_h = title_dst_h;
}

Menu::~Menu()
{
    if (title != nullptr)
        delete title;
    for (auto item : items)
    {
        if (item != nullptr)

            delete item;
    }
    items.clear();
}

void Menu::add_title(std::string title_text, int x_pos, int y_pos)
{
    if (title_font != nullptr)
    {
        if (title != nullptr)
        {
            delete title; // Clear the previous title
            title = nullptr;
        }

        title = new MenuText(title_font, title_text, title_color, renderer, x_pos, y_pos, title_dst_w, title_dst_h);
    }
}

void Menu::add_item(std::string item_text, int y_pos)
{
    if (item_font != nullptr)
    {
        int width, height, screen_width, screen_height;
        TTF_SizeText(item_font, item_text.c_str(), &width, &height);

        SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
        MenuText *new_item = new MenuText(item_font, item_text, item_color, renderer, (screen_width - width) / 2, y_pos, width, height);
        if (!items.size())
            new_item->set_color(active_item_color.r, active_item_color.g, active_item_color.b); //Sets the color of the first item to the active item color
        items.push_back(new_item);
        item_count++;
    }
}

void Menu::render()
{
    if (title != nullptr)
        title->render(renderer);

    for (auto item : items)
        if (item != nullptr)
            item->render(renderer);
}

void Menu::handle_input(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
        case SDLK_UP:
            if (items[active_index] != nullptr)
                items[active_index]->set_color(item_color.r, item_color.g, item_color.b); //Clear the color on the previous item

            active_index = active_index > 0 ? active_index - 1 : item_count - 1; //If it's larger than 0 decrement it, else set it to the last index of the items

            if (items[active_index] != nullptr)
                items[active_index]->set_color(active_item_color.r, active_item_color.g, active_item_color.b); //Make the new item active
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if (items[active_index] != nullptr)
                items[active_index]->set_color(item_color.r, item_color.g, item_color.b); //Clear the color on the previous item

            active_index = active_index >= item_count - 1 ? 0 : active_index + 1; //If it's at the last index set it to 0, else incerement it

            if (items[active_index] != nullptr)
                items[active_index]->set_color(active_item_color.r, active_item_color.g, active_item_color.b); //Make the new item active
            break;
        case SDLK_RETURN:
            break;
        default:
            break;
        }
    }
}

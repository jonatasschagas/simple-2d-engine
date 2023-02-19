#include "LTexture.hpp"
#include "SDL_image.h"

LTexture::LTexture()
{
    //Initialize
    m_pTexture = NULL;
    m_width = 0;
    m_height = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile(SDL_Renderer* pRenderer, std::string path )
{
    //Get rid of preexisting texture
    free();
    
    //The final texture
    SDL_Texture* pNewTexture = NULL;
    
    //Load image at specified path
    SDL_Surface* pLoadedSurface = IMG_Load( path.c_str() );
    if( pLoadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( pLoadedSurface, SDL_TRUE, SDL_MapRGB( pLoadedSurface->format, 0, 0xFF, 0xFF ) );
        
        //Create texture from surface pixels
        pNewTexture = SDL_CreateTextureFromSurface( pRenderer, pLoadedSurface );
        if( pNewTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            m_width = pLoadedSurface->w;
            m_height = pLoadedSurface->h;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( pLoadedSurface );
    }
    
    //Return success
    m_pTexture = pNewTexture;
    return m_pTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( m_pTexture != NULL )
    {
        SDL_DestroyTexture( m_pTexture );
        m_pTexture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( m_pTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( m_pTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( m_pTexture, alpha );
}

void LTexture::render(SDL_Renderer* pRenderer,
                      float x,
                      float y,
                      SDL_Rect* pClip,
                      float w,
                      float h,
                      float angle,
                      bool flipHorizontal)
{
    //Set rendering space and render to screen
    SDL_FRect renderQuad = { x, y, w, h };
    
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (flipHorizontal)
    {
        flip = SDL_FLIP_HORIZONTAL;
        
    }
    
    SDL_RenderCopyExF(pRenderer, m_pTexture, pClip, &renderQuad, angle, NULL, flip);
}

int LTexture::getWidth()
{
    return m_width;
}

int LTexture::getHeight()
{
    return m_height;
}

SDL_Texture* LTexture::getTexture()
{
    return m_pTexture;
}
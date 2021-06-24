#pragma once

// License: zlib
// Copyright (c) 2019 Juliette Foucaut & Doug Binks
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

/*
API BREAKING CHANGES
====================
- 2020/04/22 - Added tooltipCallback parameter to ImGui::MarkdownConfig
- 2019/02/01 - Changed LinkCallback parameters, see https://github.com/juliettef/imgui_markdown/issues/2
- 2019/02/05 - Added imageCallback parameter to ImGui::MarkdownConfig
- 2019/02/06 - Added useLinkCallback member variable to MarkdownImageData to configure using images as links
*/


#include <stdint.h>

namespace ImGui
{

    //-----------------------------------------------------------------------------
    // Basic types
    //-----------------------------------------------------------------------------

    struct Link;
    struct MarkdownConfig;

    struct MarkdownLinkCallbackData                                 // for both links and images
    {
        const char*             text;                               // text between square brackets []
        int                     textLength;
        const char*             link;                               // text between brackets ()
        int                     linkLength;
        void*                   userData;
        bool                    isImage;                            // true if '!' is detected in front of the link syntax
    };

    struct MarkdownTooltipCallbackData                              // for tooltips
    {
        MarkdownLinkCallbackData linkData;
        const char*              linkIcon;
    };

    struct MarkdownImageData
    {
        bool                    isValid = false;                    // if true, will draw the image
        bool                    useLinkCallback = false;            // if true, linkCallback will be called when image is clicked
        ImTextureID             user_texture_id = 0;                // see ImGui::Image
        ImVec2                  size = ImVec2( 100.0f, 100.0f );    // see ImGui::Image
        ImVec2                  uv0 = ImVec2( 0, 0 );               // see ImGui::Image
        ImVec2                  uv1 = ImVec2( 1, 1 );               // see ImGui::Image
        ImVec4                  tint_col = ImVec4( 1, 1, 1, 1 );    // see ImGui::Image
        ImVec4                  border_col = ImVec4( 0, 0, 0, 0 );  // see ImGui::Image
    };

    enum class MarkdownFormatType
    {
         NORMAL_TEXT,
         HEADING,
         UNORDERED_LIST,
         LINK,
         EMPHASIS,
    };

    struct MarkdownFormatInfo
    {
        MarkdownFormatType      type    = MarkdownFormatType::NORMAL_TEXT;
        int32_t                 level   = 0;                               // Set for headings: 1 for H1, 2 for H2 etc.
        bool                    itemHovered = false;                       // Currently only set for links when mouse hovered, only valid when start_ == false
        const MarkdownConfig*   config  = NULL;
    };

    typedef void                MarkdownLinkCallback( MarkdownLinkCallbackData data );
    typedef void                MarkdownTooltipCallback( MarkdownTooltipCallbackData data );

    inline void defaultMarkdownTooltipCallback( MarkdownTooltipCallbackData data_ )
    {
        if( data_.linkData.isImage )
        {
            ImGui::SetTooltip( "%.*s", data_.linkData.linkLength, data_.linkData.link );
        }
        else
        {
            ImGui::SetTooltip( "%s Open in browser\n%.*s", data_.linkIcon, data_.linkData.linkLength, data_.linkData.link );
        }
    }

    typedef MarkdownImageData   MarkdownImageCallback( MarkdownLinkCallbackData data );
    typedef void                MarkdownFormalCallback( const MarkdownFormatInfo& markdownFormatInfo_, bool start_ );

    inline void defaultMarkdownFormatCallback( const MarkdownFormatInfo& markdownFormatInfo_, bool start_ );

    struct MarkdownHeadingFormat
    {
        ImFont*                 font;                               // ImGui font
        bool                    separator;                          // if true, an underlined separator is drawn after the header
    };

    // Configuration struct for Markdown
    // - linkCallback is called when a link is clicked on
    // - linkIcon is a string which encode a "Link" icon, if available in the current font (e.g. linkIcon = ICON_FA_LINK with FontAwesome + IconFontCppHeaders https://github.com/juliettef/IconFontCppHeaders)
    // - headingFormats controls the format of heading H1 to H3, those above H3 use H3 format
    struct MarkdownConfig
    {
        static const int        NUMHEADINGS = 3;

        MarkdownLinkCallback*   linkCallback = NULL;
        MarkdownTooltipCallback* tooltipCallback = NULL;
        MarkdownImageCallback*  imageCallback = NULL;
        const char*             linkIcon = "";                      // icon displayd in link tooltip
        MarkdownHeadingFormat   headingFormats[ NUMHEADINGS ] = { { NULL, true }, { NULL, true }, { NULL, true } };
        void*                   userData = NULL;
        MarkdownFormalCallback* formatCallback = defaultMarkdownFormatCallback;
    };

    //-----------------------------------------------------------------------------
    // External interface
    //-----------------------------------------------------------------------------

    inline void Markdown( const char* markdown_, size_t markdownLength_, const MarkdownConfig& mdConfig_ );

    //-----------------------------------------------------------------------------
    // Internals
    //-----------------------------------------------------------------------------

    struct TextRegion;
    struct Line;
    inline void UnderLine( ImColor col_ );
    inline void RenderLine( const char* markdown_, Line& line_, TextRegion& textRegion_, const MarkdownConfig& mdConfig_ );

    struct TextRegion
    {
        TextRegion() : indentX( 0.0f )
        {
        }
        ~TextRegion()
        {
            ResetIndent();
        }

        // ImGui::TextWrapped will wrap at the starting position
        // so to work around this we render using our own wrapping for the first line
        void RenderTextWrapped( const char* text_, const char* text_end_, bool bIndentToHere_ = false )
        {
            float       scale = ImGui::GetIO().FontGlobalScale;
            float       widthLeft = GetContentRegionAvail().x;
            const char* endLine = ImGui::GetFont()->CalcWordWrapPositionA( scale, text_, text_end_, widthLeft );
            ImGui::TextUnformatted( text_, endLine );
            if( bIndentToHere_ )
            {
                float indentNeeded = GetContentRegionAvail().x - widthLeft;
                if( indentNeeded )
                {
                    ImGui::Indent( indentNeeded );
                    indentX += indentNeeded;
                }
            }
            widthLeft = GetContentRegionAvail().x;
            while( endLine < text_end_ )
            {
                text_ = endLine;
                if( *text_ == ' ' ) { ++text_; }    // skip a space at start of line
                endLine = ImGui::GetFont()->CalcWordWrapPositionA( scale, text_, text_end_, widthLeft );
                if( text_ == endLine ) 
                {
                    endLine++;
                }
                ImGui::TextUnformatted( text_, endLine );
            }
        }

        void RenderListTextWrapped( const char* text_, const char* text_end_ )
        {
            ImGui::Bullet();
            ImGui::SameLine();
            RenderTextWrapped( text_, text_end_, true );
        }

        bool RenderLinkText( const char* text_, const char* text_end_, const Link& link_,
            const char* markdown_, const MarkdownConfig& mdConfig_, const char** linkHoverStart_ );

        void RenderLinkTextWrapped( const char* text_, const char* text_end_, const Link& link_,
            const char* markdown_, const MarkdownConfig& mdConfig_, const char** linkHoverStart_, bool bIndentToHere_ = false );

        void RenderHelpMarker( const char* text_, const char* text_end_, const MarkdownConfig& mdConfig_ );

        void ResetIndent()
        {
            if( indentX > 0.0f )
            {
                ImGui::Unindent( indentX );
            }
            indentX = 0.0f;
        }

    private:
        float       indentX;
    };

      // Text that starts after a new line (or at beginning) and ends with a newline (or at end)
      struct Line {
          bool isHeading = false;
          bool isEmphasis = false;
          bool isUnorderedListStart = false;
          bool isLeadingSpace = true;     // spaces at start of line
          int  leadSpaceCount = 0;
          int  headingCount = 0;
          int  emphasisCount = 0;
          int  lineStart = 0;
          int  lineEnd   = 0;
          int  lastRenderPosition = 0;     // lines may get rendered in multiple pieces
      };

      struct TextBlock {                  // subset of line
          int start = 0;
          int stop  = 0;
          int size() const
          {
              return stop - start;
          }
      };

    struct Link {
        enum LinkState {
            NO_LINK,
            HAS_SQUARE_BRACKET_OPEN,
            HAS_SQUARE_BRACKETS,
            HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN,
        };
        LinkState state = NO_LINK;
        TextBlock text;
        TextBlock url;
        bool isImage = false;
        int num_brackets_open = 0;
    };

    struct Emphasis {
      enum EmphasisState {
        NONE,
        LEFT,
        MIDDLE,
        RIGHT,
      };
      EmphasisState state = NONE;
      TextBlock text;
      char sym;
    };

    struct HelpMark {
      enum HelpMarkState {
        NONE,
        LEFT_TILDE,
        RIGHT_TILDE,
      };
      HelpMarkState state = NONE;
      TextBlock text;
      char sym;
    };

    inline void UnderLine( ImColor col_ )
    {
        ImVec2 min = ImGui::GetItemRectMin();
        ImVec2 max = ImGui::GetItemRectMax();
        min.y = max.y;
        ImGui::GetWindowDrawList()->AddLine( min, max, col_, 1.0f );
    }

    inline void RenderLine( const char* markdown_, Line& line_, TextRegion& textRegion_, const MarkdownConfig& mdConfig_ )
    {
        // indent
        int indentStart = 0;
        if( line_.isUnorderedListStart )    // ImGui unordered list render always adds one indent
        {
            indentStart = 1;
        }
        for( int j = indentStart; j < line_.leadSpaceCount / 2; ++j )    // add indents
        {
            ImGui::Indent();
        }

        // render
        MarkdownFormatInfo formatInfo;
        formatInfo.config = &mdConfig_;
        int textStart = line_.lastRenderPosition + 1;
        int textSize = line_.lineEnd - textStart;
        if( line_.isUnorderedListStart )    // render unordered list
        {
            formatInfo.type = MarkdownFormatType::UNORDERED_LIST;
            mdConfig_.formatCallback( formatInfo, true );
            const char* text = markdown_ + textStart + 1;
            textRegion_.RenderListTextWrapped( text, text + textSize - 1 );
        }
        else if( line_.isHeading )          // render heading
        {
            formatInfo.level = line_.headingCount;
            formatInfo.type = MarkdownFormatType::HEADING;
            mdConfig_.formatCallback( formatInfo, true );
            const char* text = markdown_ + textStart + 1;
            textRegion_.RenderTextWrapped( text, text + textSize - 1 );
        }
		else if( line_.isEmphasis )         // render emphasis
		{
			formatInfo.level = line_.emphasisCount;
			formatInfo.type = MarkdownFormatType::EMPHASIS;
			mdConfig_.formatCallback(formatInfo, true);
			const char* text = markdown_ + textStart;
			textRegion_.RenderTextWrapped(text, text + textSize);
		}
        else                                // render a normal paragraph chunk
        {
            formatInfo.type = MarkdownFormatType::NORMAL_TEXT;
            mdConfig_.formatCallback( formatInfo, true );
            const char* text = markdown_ + textStart;
            textRegion_.RenderTextWrapped( text, text + textSize );
        }
        mdConfig_.formatCallback( formatInfo, false );

        // unindent
        for( int j = indentStart; j < line_.leadSpaceCount / 2; ++j )
        {
            ImGui::Unindent();
        }
    }

    // render markdown
    inline void Markdown( const char* markdown_, size_t markdownLength_, const MarkdownConfig& mdConfig_ )
    {
        static const char* linkHoverStart = NULL; // we need to preserve status of link hovering between frames
        Line        line;
        Link        link;
        Emphasis    em;
        HelpMark    hm;
        TextRegion  textRegion;

        char c = 0;
        for( int i=0; i < (int)markdownLength_; ++i )
        {
            c = markdown_[i];               // get the character at index
            if( c == 0 ) { break; }         // shouldn't happen but don't go beyond 0.

            // If we're at the beginning of the line, count any spaces
            if( line.isLeadingSpace )
            {
                if( c == ' ' )
                {
                    ++line.leadSpaceCount;
                    continue;
                }
                else
                {
                    line.isLeadingSpace = false;
                    line.lastRenderPosition = i - 1;
                    if(( c == '*' ) && ( line.leadSpaceCount >= 2 ))
                    {
                        if( ( (int)markdownLength_ > i + 1 ) && ( markdown_[ i + 1 ] == ' ' ) )    // space after '*'
                        {
                            line.isUnorderedListStart = true;
                            ++i;
                            ++line.lastRenderPosition;
                        }
                        // carry on processing as could be emphasis
                    }
                    else if( c == '#' )
                    {
                        line.headingCount++;
                        bool bContinueChecking = true;
                        int j = i;
                        while( ++j < (int)markdownLength_ && bContinueChecking )
                        {
                            c = markdown_[j];
                            switch( c )
                            {
                            case '#':
                                line.headingCount++;
                                break;
                            case ' ':
                                line.lastRenderPosition = j - 1;
                                i = j;
                                line.isHeading = true;
                                bContinueChecking = false;
                                break;
                            default:
                                line.isHeading = false;
                                bContinueChecking = false;
                                break;
                            }
                        }
                        if( line.isHeading )
                        {
                            // reset emphasis status, we do not support emphasis around headers for now
                            em = Emphasis();
                            continue;
                        }
                    }
                }
            }
            // Test to see if we have a link
            switch( link.state )
              {
              case Link::NO_LINK:
                  if( c == '[' && !line.isHeading ) // we do not support headings with links for now
                  {
                      link.state = Link::HAS_SQUARE_BRACKET_OPEN;
                      link.text.start = i + 1;
                      if( i > 0 && markdown_[i - 1] == '!' )
                      {
                          link.isImage = true;
                      }
                  }
                  break;
              case Link::HAS_SQUARE_BRACKET_OPEN:
                  if( c == ']' )
                  {
                      link.state = Link::HAS_SQUARE_BRACKETS;
                      link.text.stop = i;
                  }
                  break;
              case Link::HAS_SQUARE_BRACKETS:
                  if( c == '(' )
                  {
                      link.state = Link::HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN;
                      link.url.start = i + 1;
                      link.num_brackets_open = 1;
                  }
                  break;
              case Link::HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN:
                  if( c == '(' )
                  {
                      ++link.num_brackets_open;
                  }
                  else if( c == ')' )
                  {
                      --link.num_brackets_open;
                  }
                  if( link.num_brackets_open == 0 )
                  {
                      // reset emphasis status, we do not support emphasis around links for now
                      em = Emphasis();
                      // render previous line content
                      line.lineEnd = link.text.start - ( link.isImage ? 2 : 1 );
                      RenderLine( markdown_, line, textRegion, mdConfig_ );
                      line.leadSpaceCount = 0;
                      link.url.stop = i;
                      line.isUnorderedListStart = false;    // the following text shouldn't have bullets
                      ImGui::SameLine( 0.0f, 0.0f );
                      if( link.isImage )   // it's an image, render it.
                      {
                          bool drawnImage = false;
                          bool useLinkCallback = false;
                          if( mdConfig_.imageCallback )
                          {
                              MarkdownImageData imageData = mdConfig_.imageCallback( { markdown_ + link.text.start, link.text.size(), markdown_ + link.url.start, link.url.size(), mdConfig_.userData, true } );
                              useLinkCallback = imageData.useLinkCallback;
                              if( imageData.isValid )
                              {
                                  ImGui::Image( imageData.user_texture_id, imageData.size, imageData.uv0, imageData.uv1, imageData.tint_col, imageData.border_col );
                                  drawnImage = true;
                              }
                          }
                          if( !drawnImage )
                          {
                              ImGui::Text( "( Image %.*s not loaded )", link.url.size(), markdown_ + link.url.start );
                          }
                          if( ImGui::IsItemHovered() )
                          {
                              if( ImGui::IsMouseReleased( 0 ) && mdConfig_.linkCallback && useLinkCallback )
                              {
                                  mdConfig_.linkCallback( { markdown_ + link.text.start, link.text.size(), markdown_ + link.url.start, link.url.size(), mdConfig_.userData, true } );
                              }
                              if( link.text.size() > 0 && mdConfig_.tooltipCallback )
                              {
                                  mdConfig_.tooltipCallback( { { markdown_ + link.text.start, link.text.size(), markdown_ + link.url.start, link.url.size(), mdConfig_.userData, true }, mdConfig_.linkIcon } );
                              }
                          }
                      }
                      else                 // it's a link, render it.
                      {
                          textRegion.RenderLinkTextWrapped( markdown_ + link.text.start, markdown_ + link.text.start + link.text.size(), link, markdown_, mdConfig_, &linkHoverStart, false );
                      }
                      ImGui::SameLine( 0.0f, 0.0f );
                      // reset the link by reinitializing it
                      link = Link();
                      line.lastRenderPosition = i;
                      break;
                  }
              }
            // Test to see if we have emphasis styling
            switch( em.state )
            {
            case Emphasis::NONE:
              if( link.state == Link::NO_LINK && !line.isHeading )
                      {
                          int next = i + 1;
                          int prev = i - 1;
                if( ( c == '*' || c == '_' )
                              && ( i == line.lineStart
                                  || markdown_[ prev ] == ' '
                                  || markdown_[ prev ] == '\t' ) // emphasis must be preceded by whitespace or line start
                              && (int)markdownLength_ > next // emphasis must precede non-whitespace
                              && markdown_[ next ] != ' '
                              && markdown_[ next ] != '\n'
                              && markdown_[ next ] != '\t' )
                          {
                  em.state = Emphasis::LEFT;
                  em.sym = c;
                  em.text.start = i;
                  line.emphasisCount = 1;
                  continue;
                }
              }
              break;
            case Emphasis::LEFT:
              if( em.sym == c )
                      {
                ++line.emphasisCount;
                continue;
              }
                      else
                      {
                em.text.start = i;
                em.state = Emphasis::MIDDLE;
              }
              break;
            case Emphasis::MIDDLE:
              if( em.sym == c )
                      {
                em.state = Emphasis::RIGHT;
                em.text.stop = i;
                        // pass through to case Emphasis::RIGHT
              }
                      else
                      {
                          break;
                      }
            case Emphasis::RIGHT:
              if( em.sym == c )
                      {
                if( line.emphasisCount < 3 && ( i - em.text.stop + 1 == line.emphasisCount ) )
                          {
                            // render text up to emphasis
                            int lineEnd = em.text.start - line.emphasisCount;
                            if( lineEnd > line.lineStart )
                            {
                                line.lineEnd = lineEnd;
                                RenderLine( markdown_, line, textRegion, mdConfig_ );
                                ImGui::SameLine( 0.0f, 0.0f );
                                line.isUnorderedListStart = false;
                                line.leadSpaceCount = 0;
                            }
                            line.isEmphasis = true;
                            line.lastRenderPosition = em.text.start - 1;
                            line.lineStart = em.text.start;
                            line.lineEnd = em.text.stop;
                            RenderLine( markdown_, line, textRegion, mdConfig_ );
                            ImGui::SameLine( 0.0f, 0.0f );
                            line.isEmphasis = false;
                            line.lastRenderPosition = i;
                            em = Emphasis();
                          }
                          continue;
                      }
                      else
                      {
                          em.state = Emphasis::NONE;
                          // render text up to here
                          int start = em.text.start - line.emphasisCount;
                          if( start < line.lineStart )
                          {
                              line.lineEnd = line.lineStart;
                              line.lineStart = start;
                              line.lastRenderPosition = start - 1;
                              RenderLine(markdown_, line, textRegion, mdConfig_);
                              line.lineStart          = line.lineEnd;
                              line.lastRenderPosition = line.lineStart - 1;
                          }
                      }
              break;
            }
            // Test to see if we have a help marker
            switch( hm.state )
            {
              case HelpMark::NONE:
                if( c == '~')
                {
                    hm.state = HelpMark::LEFT_TILDE;
                    hm.text.start = i + 1;
                }
                break;
              case HelpMark::LEFT_TILDE:
                if( c == '~' ) {
                  hm.state = HelpMark::RIGHT_TILDE;
                  hm.text.stop = i;
                }
                break;

              case HelpMark::RIGHT_TILDE:
                line.lineEnd = hm.text.start - 1;
                RenderLine( markdown_, line, textRegion, mdConfig_ );
                line.leadSpaceCount = 0;
                line.isUnorderedListStart = false;    // the following text shouldn't have bullets

                ImGui::SameLine( 0.0f, 0.0f );
                textRegion.RenderHelpMarker( markdown_ + hm.text.start, markdown_ + hm.text.stop, mdConfig_ );
                ImGui::SameLine( 0.0f, 0.0f );
                hm = HelpMark();
                line.lastRenderPosition = i - 1;
                break;
            }
            // handle end of line (render)
            if( c == '\n' )
            {
                // first check if the line is a horizontal rule
                line.lineEnd = i;
                if( em.state == Emphasis::MIDDLE && line.emphasisCount >=3 &&
                    ( line.lineStart + line.emphasisCount ) == i )
                {
                    ImGui::Separator();
                }
                else
                {
                    // render the line: multiline emphasis requires a complex implementation so not supporting
                    RenderLine( markdown_, line, textRegion, mdConfig_ );
                }

                // reset the line and emphasis state
                line = Line();
                em = Emphasis();

                line.lineStart = i + 1;
                line.lastRenderPosition = i;

                textRegion.ResetIndent();
                // reset the link
                link = Link();
              }
        }

        if( em.state == Emphasis::LEFT && line.emphasisCount >= 3 )
        {
            ImGui::Separator();
        }
        else
        {
            // render any remaining text if last char wasn't 0
            if( markdownLength_ && line.lineStart < (int)markdownLength_ && markdown_[ line.lineStart ] != 0 )
            {
                // handle both null terminated and non null terminated strings
                line.lineEnd = (int)markdownLength_;
                if( 0 == markdown_[ line.lineEnd - 1 ] )
                {
                    --line.lineEnd;
                }
                RenderLine( markdown_, line, textRegion, mdConfig_ );
            }
        }
    }

    inline bool TextRegion::RenderLinkText( const char* text_, const char* text_end_, const Link& link_,
        const char* markdown_, const MarkdownConfig& mdConfig_, const char** linkHoverStart_ )
    {
        MarkdownFormatInfo formatInfo;
        formatInfo.config = &mdConfig_;
        formatInfo.type = MarkdownFormatType::LINK;
        mdConfig_.formatCallback( formatInfo, true );
        ImGui::PushTextWrapPos( -1.0f );
        ImGui::TextUnformatted( text_, text_end_ );
        ImGui::PopTextWrapPos();

        bool bThisItemHovered = ImGui::IsItemHovered();
        if(bThisItemHovered)
        {
            *linkHoverStart_ = markdown_ + link_.text.start;
        }
        bool bHovered = bThisItemHovered || ( *linkHoverStart_ == ( markdown_ + link_.text.start ) );

        formatInfo.itemHovered = bHovered;
        mdConfig_.formatCallback( formatInfo, false );

        if(bHovered)
        {
            if( ImGui::IsMouseReleased( 0 ) && mdConfig_.linkCallback )
            {
                mdConfig_.linkCallback( { markdown_ + link_.text.start, link_.text.size(), markdown_ + link_.url.start, link_.url.size(), mdConfig_.userData, false } );
            }
            if( mdConfig_.tooltipCallback )
            {
                mdConfig_.tooltipCallback( { { markdown_ + link_.text.start, link_.text.size(), markdown_ + link_.url.start, link_.url.size(), mdConfig_.userData, false }, mdConfig_.linkIcon } );
            }
        }
        return bThisItemHovered;
    }

    inline void TextRegion::RenderLinkTextWrapped( const char* text_, const char* text_end_, const Link& link_,
        const char* markdown_, const MarkdownConfig& mdConfig_, const char** linkHoverStart_, bool bIndentToHere_ )
        {
            float       scale = ImGui::GetIO().FontGlobalScale;
            float       widthLeft = GetContentRegionAvail().x;
            const char* endLine = ImGui::GetFont()->CalcWordWrapPositionA( scale, text_, text_end_, widthLeft );
            bool bHovered = RenderLinkText( text_, endLine, link_, markdown_, mdConfig_, linkHoverStart_ );
            if( bIndentToHere_ )
            {
                float indentNeeded = GetContentRegionAvail().x - widthLeft;
                if( indentNeeded )
                {
                    ImGui::Indent( indentNeeded );
                    indentX += indentNeeded;
                }
            }
            widthLeft = GetContentRegionAvail().x;
            while( endLine < text_end_ )
            {
                text_ = endLine;
                if( *text_ == ' ' ) { ++text_; }    // skip a space at start of line
                endLine = ImGui::GetFont()->CalcWordWrapPositionA( scale, text_, text_end_, widthLeft );
                if( text_ == endLine )
                {
                    endLine++;
                }
                bool bThisLineHovered = RenderLinkText( text_, endLine, link_, markdown_, mdConfig_, linkHoverStart_ );
                bHovered = bHovered || bThisLineHovered;
            }
            if( !bHovered && *linkHoverStart_ == markdown_ + link_.text.start )
            {
                *linkHoverStart_ = NULL;
            }
        }


    inline void defaultMarkdownFormatCallback( const MarkdownFormatInfo& markdownFormatInfo_, bool start_ )
    {
        switch( markdownFormatInfo_.type )
        {
        case MarkdownFormatType::NORMAL_TEXT:
            break;
		    case MarkdownFormatType::EMPHASIS:
        {
            MarkdownHeadingFormat fmt;
            // default styling for emphasis uses last headingFormats - for your own styling
            // implement EMPHASIS in your formatCallback
            if( markdownFormatInfo_.level == 1 )
            {
                // normal emphasis
 			    if( start_ )
			    {
                    ImGui::PushStyleColor( ImGuiCol_Text, ImGui::GetStyle().Colors[ ImGuiCol_TextDisabled ] );
			    }
                else
			    {
                    ImGui::PopStyleColor();
			    }              
            }
            else
            {
                // strong emphasis
                fmt = markdownFormatInfo_.config->headingFormats[ MarkdownConfig::NUMHEADINGS - 1 ];
			    if( start_ )
			    {
				    if( fmt.font )
				    {
					    ImGui::PushFont( fmt.font );
				    }
			    }
                else
			    {
				    if( fmt.font )
				    {
					    ImGui::PopFont();
				    }
			    }
            }
            break;
        }
        case MarkdownFormatType::HEADING:
        {
            MarkdownHeadingFormat fmt;
            if( markdownFormatInfo_.level > MarkdownConfig::NUMHEADINGS )
            {
                fmt = markdownFormatInfo_.config->headingFormats[ MarkdownConfig::NUMHEADINGS - 1 ];
            }
            else
            {
                fmt = markdownFormatInfo_.config->headingFormats[ markdownFormatInfo_.level - 1 ];
            }
            if( start_ )
            {
                if( fmt.font  )
                {
                    ImGui::PushFont( fmt.font );
                }
                ImGui::NewLine();
            }
            else
            {
                if( fmt.separator )
                {
                    ImGui::Separator();
                    ImGui::NewLine();
                }
                else
                {
                    ImGui::NewLine();
                }
                if( fmt.font )
                {
                    ImGui::PopFont();
                }
            }
            break;
        }
        case MarkdownFormatType::UNORDERED_LIST:
            break;
        case MarkdownFormatType::LINK:
            if( start_ )
            {
                ImGui::PushStyleColor( ImGuiCol_Text, ImGui::GetStyle().Colors[ ImGuiCol_ButtonHovered ] );
            }
            else
            {
                ImGui::PopStyleColor();
                if( markdownFormatInfo_.itemHovered )
                {
                    ImGui::UnderLine( ImGui::GetStyle().Colors[ ImGuiCol_ButtonHovered ] );
                }
                else
                {
                    ImGui::UnderLine( ImGui::GetStyle().Colors[ ImGuiCol_Button ] );
                }
            }
            break;
        }
    }

    //-----------------------------------------------------------------------------
    // Custom stuff
    //-----------------------------------------------------------------------------
    inline void TextRegion::RenderHelpMarker( const char* text_, const char* text_end_, const MarkdownConfig& mdConfig_ )
    {
        MarkdownFormatInfo formatInfo;
        formatInfo.config = &mdConfig_;
        formatInfo.type = MarkdownFormatType::NORMAL_TEXT;
        mdConfig_.formatCallback( formatInfo, true );

        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(text_, text_end_);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

}

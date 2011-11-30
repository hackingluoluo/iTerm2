//
//  TmuxLayoutParser.h
//  iTerm
//
//  Created by George Nachman on 11/28/11.
//

#import <Cocoa/Cocoa.h>

// Trees consist of arrays of dictionaries. The dictionaries have these keys defined:
extern NSString *kLayoutDictChildrenKey;  // Sub-tree. Returns an array.
extern NSString *kLayoutDictWidthKey;     // Width of node. String. Use -intValue.
extern NSString *kLayoutDictHeightKey;    // Height. String. Use -intValue.
extern NSString *kLayoutDictXOffsetKey;   // X position. String. Use -intValue.
extern NSString *kLayoutDictYOffsetKey;   // Y position. String. Use -intValue.
extern NSString *kLayoutDictNodeType;     // Node type from enum LayoutNodeType. NSNumber.
extern NSString *kLayoutDictWindowPaneKey;  // window pane number (leaf nodes only)

// These values are filled in by the client:
extern NSString *kLayoutDictPixelWidthKey;
extern NSString *kLayoutDictPixelHeightKey;
extern NSString *kLayoutDictHistoryKey;       // Array of screen_char_t-filled NSData
extern NSString *kLayoutDictAltHistoryKey;    // Alternate screen history

typedef enum {
    kLeafLayoutNode,
    kHSplitLayoutNode,
    kVSplitLayoutNode
} LayoutNodeType;

@interface TmuxLayoutParser : NSObject

+ (TmuxLayoutParser *)sharedInstance;
- (NSMutableDictionary *)parsedLayoutFromString:(NSString *)layout;
- (NSMutableDictionary *)windowPane:(int)windowPane
                        inParseTree:(NSMutableDictionary *)parseTree;

// For each leaf node, perform selector taking the NSMutableDictionary for the
// current node as the first arg and obj as the second arg. If it returns
// nil, the DFS continues; otherwise the DFS stops and that value is returned
// here.
- (id)depthFirstSearchParseTree:(NSMutableDictionary *)parseTree
                callingSelector:(SEL)selector
                       onTarget:(id)target
                     withObject:(id)obj;

@end

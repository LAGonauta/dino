using Dino.Entities;
using Qlite;

namespace Dino {

public class Util {
    public static Message.Type get_message_type_for_conversation(Conversation conversation) {
        switch (conversation.type_) {
            case Conversation.Type.CHAT:
                return Entities.Message.Type.CHAT;
            case Conversation.Type.GROUPCHAT:
                return Entities.Message.Type.GROUPCHAT;
            case Conversation.Type.GROUPCHAT_PM:
                return Entities.Message.Type.GROUPCHAT_PM;
            default:
                assert_not_reached();
        }
    }

    public static Conversation.Type get_conversation_type_for_message(Message message) {
        switch (message.type_) {
            case Entities.Message.Type.CHAT:
                return Conversation.Type.CHAT;
            case Entities.Message.Type.GROUPCHAT:
                return Conversation.Type.GROUPCHAT;
            case Entities.Message.Type.GROUPCHAT_PM:
                return Conversation.Type.GROUPCHAT_PM;
            default:
                assert_not_reached();
        }
    }

    public static bool is_pixbuf_supported_mime_type(string mime_type) {
        if (mime_type == null) return false;

        foreach (Gdk.PixbufFormat pixbuf_format in Gdk.Pixbuf.get_formats()) {
            foreach (string pixbuf_mime in pixbuf_format.get_mime_types()) {
                if (pixbuf_mime == mime_type) return true;
            }
        }
        return false;
    }
    
    public static void launch_default_for_uri(string file_uri)
    {
#if _WIN32
        // This should respect the mark of the web, unlike ShellExecute
        string[] argv = { "explorer.exe", file_uri };
        try {
            var process = new Subprocess.newv(argv, SubprocessFlags.NONE);
            process.wait();
        } catch (Error e) {
        }
#else
        AppInfo.launch_default_for_uri(file_uri, null);
#endif
    }
    
    public static string get_content_type(FileInfo fileInfo)
    {
#if _WIN32
        string fileName = fileInfo.get_name();
        int fileNameLength = fileName.length;
        int extIndex = fileName.last_index_of(".");
        if (extIndex < fileNameLength)
        {
            string extension = fileName.substring(extIndex, fileNameLength - extIndex);
            string mime_type = ContentType.get_mime_type(extension);
            if (mime_type != null && mime_type.length != 0)
            {
                return mime_type;
            }
        }
#endif
        return fileInfo.get_content_type();
    }
}

}

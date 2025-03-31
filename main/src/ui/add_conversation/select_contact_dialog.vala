using Gee;
using Gdk;
using Gtk;

using Dino.Entities;
using Xmpp;

namespace Dino.Ui {

public class SelectContactDialog : Gtk.Dialog {

    public signal void selected(Account account, Jid jid);

    public Button ok_button;

    private RosterList roster_list;
    private ListBox roster_list_box;
    private SelectJidFragment select_jid_fragment;
    private StreamInteractor stream_interactor;
    private Gee.List<Account> accounts;

    public SelectContactDialog(StreamInteractor stream_interactor, Gee.List<Account> accounts) {
        Object(use_header_bar : 1);
        modal = true;
        this.default_width = 460;
        this.default_height = 550;

        this.stream_interactor = stream_interactor;
        this.accounts = accounts;

        setup_view();
        setup_headerbar();
    }

    public void set_filter(string str) {
        select_jid_fragment.set_filter(str);
    }

    private void setup_headerbar() {
        Button cancel_button = new Button();
        cancel_button.set_label(_("Cancel"));
        cancel_button.visible = true;

        ok_button = new Button();
        ok_button.add_css_class("suggested-action");
        ok_button.sensitive = false;
        ok_button.visible = true;

        HeaderBar header_bar = get_header_bar() as HeaderBar;
        header_bar.show_title_buttons = false;
        header_bar.pack_start(cancel_button);
        header_bar.pack_end(ok_button);

        cancel_button.clicked.connect(() => { close(); });
        ok_button.clicked.connect(() => {
            ListRow? selected_row = roster_list_box.get_selected_row() != null ? roster_list_box.get_selected_row().get_child() as ListRow : null;
            if (selected_row != null) selected(selected_row.account, selected_row.jid);
            close();
        });
    }

    private void setup_view() {
        roster_list = new RosterList(stream_interactor, accounts);
        roster_list_box = roster_list.get_list_box();
        roster_list_box.row_activated.connect(() => { ok_button.clicked(); });
        select_jid_fragment = new SelectJidFragment(stream_interactor, roster_list_box, accounts);
        select_jid_fragment.add_jid.connect((row) => {
            AddContactDialog add_contact_dialog = new AddContactDialog(stream_interactor);
            add_contact_dialog.set_transient_for(this);
            add_contact_dialog.present();
        });
        select_jid_fragment.remove_jid.connect((row) => {
            ListRow list_row = roster_list_box.get_selected_row().child as ListRow;
            stream_interactor.get_module(RosterManager.IDENTITY).remove_jid(list_row.account, list_row.jid);
        });
        select_jid_fragment.notify["done"].connect(() => {
            ok_button.sensitive = select_jid_fragment.done;
        });
        get_content_area().append(select_jid_fragment);
    }
}

public class AddChatDialog : SelectContactDialog {

    public signal void added(Conversation conversation);

    public AddChatDialog(StreamInteractor stream_interactor, Gee.List<Account> accounts) {
        base(stream_interactor, accounts);
        title = _("Start Conversation");
        ok_button.label = _("Start");
        selected.connect((account, jid) => {
            Conversation conversation = stream_interactor.get_module(ConversationManager.IDENTITY).create_conversation(jid, account, Conversation.Type.CHAT);
            stream_interactor.get_module(ConversationManager.IDENTITY).start_conversation(conversation);
            added(conversation);
        });
    }
}

}

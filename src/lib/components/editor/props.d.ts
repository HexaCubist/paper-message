import type { User } from "@auth/sveltekit";

export interface commonProps {
  sending: boolean;
  canSend: boolean;
  disabled: boolean;
}

export interface textProps extends commonProps {
  liveText: string | undefined;
  updateText: (e: KeyboardEvent) => void;
}

export interface imageProps extends commonProps {
  liveImage: string | undefined;
  messagePreview: string | undefined;
  account?: User;
  updateImage: (data: { image: string }) => void;
}

type editorData =
  | {
      type: "text";
      content: {
        text: string;
        image?: string;
      };
    }
  | {
      type: "image";
      content: {
        image: string;
        text?: string;
      };
    };

export interface editorProps extends commonProps {
  editorData: editorData;
  account?: User;
  update: (data: editorData) => void;
}
